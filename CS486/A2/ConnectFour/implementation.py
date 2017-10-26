"""
This is the only file you should change in your submission!
"""
from basicplayer import basic_evaluate, minimax, get_all_next_moves, is_terminal
from util import memoize, run_search_function, INFINITY, NEG_INFINITY


STUDENT_ID = 20523403
AGENT_NAME = "SorryINeedToWin"
COMPETE = False


def focused_evaluate(board):
    if board.longest_chain(board.get_current_player_id()) == 4:
        score = 1001 - board.num_tokens_on_board()
    elif board.longest_chain(board.get_other_player_id()) == 4:
        score = -1001 + board.num_tokens_on_board()
    else:
        score = board.longest_chain(board.get_current_player_id()) * 10
        for row in range(6):
            for col in range(7):
                if board.get_cell(row, col) == board.get_current_player_id():
                    score -= abs(3 - col)
                elif board.get_cell(row, col) == board.get_other_player_id():
                    score += abs(3 - col)
    return score


def alpha_beta_search(board, depth, eval_fn, get_next_moves_fn=get_all_next_moves, is_terminal_fn=is_terminal):
    alpha = NEG_INFINITY
    beta = INFINITY
    best_val = None
    for move, new_board in get_next_moves_fn(board):
        v = -alpha_value(new_board, depth-1, alpha, beta, eval_fn, get_next_moves_fn, is_terminal_fn)
        if best_val == None or v > best_val[0]:
            best_val = (v, move, new_board)
    return best_val[1]


def alpha_value(board, depth, alpha, beta, eval_fn, get_next_moves_fn, is_terminal_fn):
    if is_terminal_fn(depth, board):
        return eval_fn(board)
    for move, new_board in get_next_moves_fn(board):
        beta_best_val = beta_value(new_board, depth - 1, -alpha, -beta, eval_fn, get_next_moves_fn, is_terminal_fn)
        alpha = max(alpha, -beta_best_val)
        if alpha >= beta:
            break
    return alpha


def beta_value(board, depth, alpha, beta, eval_fn, get_next_moves_fn, is_terminal_fn):
    if is_terminal_fn(depth, board):
        return eval_fn(board)
    for move, new_board in get_next_moves_fn(board):
        alpha_best_val = alpha_value(new_board, depth - 1, -alpha, -beta, eval_fn, get_next_moves_fn, is_terminal_fn)
        beta = max(beta, -alpha_best_val)
        if beta >= alpha:
            break
    return beta


def check(board, player_id):
    # check if player_id can win indirectly (next step guarantee win)
    for row in range(6):
        for col in range(3):
            if board.get_cell(row, col+1) == player_id and board.get_cell(row, col+2) == player_id and \
                     board.get_cell(row, col) == 0 and board.get_cell(row, col+3) == 0:
                if row == 5:
                    return True
                elif board.get_cell(row+1, col) != 0 and board.get_cell(row+1, col+3) != 0:
                    return True
    return False

def better_evaluate(board):
    # check if current player can win directly
    if board.longest_chain(board.get_current_player_id()) == 4:
        score = 3001 - board.num_tokens_on_board()
    # check if other player can win directly
    elif board.longest_chain(board.get_other_player_id()) == 4:
        score = -3001 + board.num_tokens_on_board()
    # check if current player can win indirectly (next step guarantee win)
    elif check(board, board.get_current_player_id()):
        score = 2001 - board.num_tokens_on_board()
    # check if other player can win indirectly (next step guarantee win)
    elif check(board, board.get_other_player_id()):
        score = -2001 + board.num_tokens_on_board()
    # otherwise, play like normal
    else:
        score = board.longest_chain(board.get_current_player_id()) * 10
        for row in range(6):
            for col in range(7):
                if board.get_cell(row, col) == board.get_current_player_id():
                    score -= abs(3-col)
                elif board.get_cell(row, col) == board.get_other_player_id():
                    score += abs(3-col)

    return score

# better_evaluate run faster
better_evaluate = memoize(better_evaluate)

# A player uses focused_evaluate
quick_to_win_player = lambda board: minimax(board, depth=4, eval_fn=focused_evaluate)

# A player that uses alpha-beta
def alpha_beta_player(board):
    return alpha_beta_search(board, depth=8, eval_fn=focused_evaluate)

# This player uses progressive deepening, so it can kick your ass while making efficient use of time
def ab_iterative_player(board):
    return run_search_function(board, search_fn=alpha_beta_search, eval_fn=focused_evaluate, timeout=5)

# A player that uses alpha-beta and better_evaluate:
def my_player(board):
    return run_search_function(board, search_fn=alpha_beta_search, eval_fn=better_evaluate, timeout=5)

# my_player = lambda board: alpha_beta_search(board, depth=4, eval_fn=better_evaluate)
