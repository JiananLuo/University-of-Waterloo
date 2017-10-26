import argparse

from connectfour import ConnectFourBoard, human_player, run_game
from basicplayer import basic_player
from implementation import quick_to_win_player, alpha_beta_player, better_evaluate, my_player

if __name__ == '__main__':
    DESCRIPTION = """Main driver to play Connect Four:
    Note, X goes before O.
    X: play game as human (X)
    O: play game as human (O)
    computer: watch computer play against itself
    quick: watch computer play against quick to win player
    alphabeta: play against alpha_beta_player
    my_player: watch my_player play against my_player
    my_player_vs_basic: watch my_player play against basic player
    debug_evaluate: print better_evaluate function return value for board
    """
    parser = argparse.ArgumentParser(description=DESCRIPTION, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('mode', type=str, help='Mode for playing Connect Four.',
                        choices=['X', 'O', 'computer', 'quick', 'alphabeta', 'my_player', 'my_player_vs_basic', 'debug_evaluate'])

    args = parser.parse_args()

    if args.mode == 'X':
        run_game(human_player, basic_player)
    elif args.mode == 'O':
        run_game(basic_player, human_player)
    elif args.mode == 'computer':
        run_game(basic_player, basic_player)
    elif args.mode == 'quick':
        run_game(basic_player, quick_to_win_player)
    elif args.mode == 'alphabeta':
        run_game(human_player, alpha_beta_player)
    elif args.mode == 'my_player':
        # watch your player play a game
        run_game(my_player, my_player)
    elif args.mode == 'my_player_vs_basic':
        run_game(my_player, basic_player)
    elif args.mode == 'debug_evaluate':
        board_tuples = ((0, 0, 0, 0, 0, 0, 0),
                        (0, 0, 0, 0, 0, 0, 0),
                        (0, 0, 0, 0, 0, 0, 0),
                        (0, 2, 2, 1, 1, 2, 0),
                        (0, 2, 1, 2, 1, 2, 0),
                        (2, 1, 2, 1, 1, 1, 0),
                        )
        test_board_1 = ConnectFourBoard(board_array=board_tuples,
                                        current_player=1)
        test_board_2 = ConnectFourBoard(board_array=board_tuples,
                                        current_player=2)
        # better evaluate from player 1
        print("{} => {}".format(test_board_1, better_evaluate(test_board_1)))
        # better evaluate from player 2
        print("{} => {}".format(test_board_2, better_evaluate(test_board_2)))
