#include "minishell.h"

/*
 * 後で消すコメント
 * 単一コマンドノード（CMD_EXEC）の実行。
 *
 * <パイプ・リダイレクト追加時の変更点>
 * - パイプ内で呼ばれる場合、子プロセス側では stdin/stdout が既に
 *   dup2 済みなので、ここは変更不要（そのまま STDOUT_FILENO に書けばよい）。
 * - ただしビルトインをパイプの一部として実行する場合は、親で直接
 *   dispatch_builtin を呼んではいけない（状態変更をサブシェルに閉じるため
 *   fork してから呼ぶ）。return (dispatch_builtin);のところを、
 *   exec_pipe 側で fork してからこの関数を呼ぶ設計にする。
 * - 親プロセスで実行するビルトインにリダイレクトが付いている場合は、
 *   （cd /tmp > out.txt やexport F00=bar > /dev/nullとか）
 *   exec_redir 側で親の fd を退避 → dup2 → exec_simple 呼び出し → 復元、
 *   という流れになる（この関数自体は変更不要）。
 */
static int	exec_simple(t_cmd_exec *cmd, t_minishell *ms)
{
	if (!cmd->args || !cmd->args[0])
		return (SUCCESS);
	if (is_builtin(cmd->args[0]))
		return (dispatch_builtin(cmd->args, ms));
	return (exec_external(cmd, ms));
}

/*
 * 後で消すコメント
 * ツリー走査のディスパッチ。node->type でサブクラスに分岐する。
 *
 * <パイプ・リダイレクト・リスト追加時の変更点>
 * ここに条件分岐を追加するだけで再帰が成立する。各ハンドラは内部で
 * 必要に応じて exec_node を再帰呼び出しする。
 *
 *   if (node->type == CMD_PIPE)
 *       return (exec_pipe((t_cmd_pipe *)node, ms));
 *       // pipe() → fork 2つ → 子それぞれで dup2 してから exec_node 再帰
 *       // → 親で 2 つの waitpid → 右側の exit_status を返す
 *
 *   if (node->type == CMD_REDIR)
 *       return (exec_redir((t_cmd_redir *)node, ms));
 *       // open(filename, mode) → 親の stdin/stdout を退避 → dup2 →
 *       // exec_node(redir->cmd_head) 再帰 → fd 復元 → close
 *       // ヒアドキュメント(<<) は事前に一時ファイルに書き込む仕組みで実装予定
 *
 *   if (node->type == CMD_LIST)
 *       return (exec_list((t_cmd_list *)node, ms));
 *       // exec_node(left) → exit_status 更新 → exec_node(right)
 *       // （; 区切りの順次実行）
 *
 * <新規に必要なファイル（想定:return内の関数を別ファイルに定義するはず。）>
 * - src/executor/exec_pipe.c
 * - src/executor/exec_redir.c
 * - src/executor/heredoc.c
 */
static int	exec_node(t_cmd_base *node, t_minishell *ms)
{
	if (!node)
		return (SUCCESS);
	if (node->type == CMD_EXEC)
		return (exec_simple((t_cmd_exec *)node, ms));
	ft_putstr_fd("executor: node type not implemented\n", STDERR_FILENO);
	return (FAILURE);
}

/*
 * 後で消すコメント
 * エントリポイント。ツリー全体を走査して最終的な exit_status を更新する。
 *
 * パイプ・リダイレクト追加時も変更不要
 */
int	executor(t_cmd_base *tree, t_minishell *ms)
{
	int	status;

	if (!tree)
		return (SUCCESS);
	status = exec_node(tree, ms);
	ms->exit_status = status;
	return (status);
}
