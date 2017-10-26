import logging
import sys
import unittest

from basicplayer import basic_player, minimax
from connectfour import ConnectFourBoard, run_game
from implementation import alpha_beta_search, better_evaluate, focused_evaluate, my_player
from tree_searcher import make_tree, tree_as_string, tree_eval, tree_get_next_move, is_leaf


class TestAlphaBetaSearch(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.log = logging.getLogger("tests")

    def _check(self, tup_tree, tree_name, expected):
        tree = make_tree(tup_tree)
        v = alpha_beta_search(tree, 10,
                              tree_eval,
                              tree_get_next_move,
                              is_leaf)
        try:
            self.assertEqual(v, expected)
        except Exception as e:
            self.log.error("%s:\n%s", tree_name, tree_as_string(tree))
            self.log.error("BEST MOVE: %s", format(v))
            self.log.error("EXPECTED: %s", format(expected))
            raise e

    def test_alpha_beta_search_1(self):
        tup_tree = ("A", None,
                    ("B", None,
                     ("C", None,
                      ("D", 2),
                      ("E", 2)),
                      ("F", None,
                      ("G", 0),
                      ("H", 4))
                     ),
                    ("I", None,
                     ("J", None,
                      ("K", 6),
                      ("L", 8)),
                     ("M", None,
                      ("N", 4),
                      ("O", 6))
                     )
                    )
        self._check(tup_tree, "TREE_1", "I")

    def test_alpha_beta_search_2(self):
        tup_tree = ("A", None,
                    ("B", None,
                     ("C", None,
                      ("D", 6),
                      ("E", 4)),
                     ("F", None,
                      ("G", 8),
                      ("H", 6))
                     ),
                    ("I", None,
                     ("J", None,
                      ("K", 4),
                      ("L", 0)),
                     ("M", None,
                      ("N", 2),
                      ("O", 2))
                     )
                    )
        self._check(tup_tree, "TREE_2", "B")

    def test_alpha_beta_search_3(self):
        tup_tree = ("A", None,
                    ("B", None,
                     ("E", None,
                      ("K", 8),
                      ("L", 2)),
                     ("F", 6)
                     ),
                    ("C", None,
                     ("G", None,
                      ("M", None,
                       ("S", 4),
                       ("T", 5)),
                      ("N", 3)),
                     ("H", None,
                      ("O", 9),
                      ("P", None,
                       ("U", 10),
                       ("V", 8))
                      ),
                     ),
                    ("D", None,
                     ("I", 1),
                     ("J", None,
                      ("Q", None,
                       ("W", 7),
                       ("X", 12)),
                      ("K", None,
                       ("Y", 11),
                       ("Z", 15)
                       ),
                      )
                     )
                    )
        self._check(tup_tree, "TREE_3", "B")


class TestConnectFourStatic(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.log = logging.getLogger("tests")

        # Obvious win
        cls.WINNING_BOARD = ConnectFourBoard(board_array=
                                             ((0, 0, 0, 0, 0, 0, 0),
                                              (0, 0, 0, 0, 0, 0, 0),
                                              (0, 0, 0, 0, 0, 0, 0),
                                              (0, 1, 0, 0, 0, 0, 0),
                                              (0, 1, 0, 0, 0, 2, 0),
                                              (0, 1, 0, 0, 2, 2, 0),
                                              ),
                                             current_player=1)

        # 2 can win, but 1 can win a lot more easily
        cls.BARELY_WINNING_BOARD = ConnectFourBoard(board_array=
                                                    ((0, 0, 0, 0, 0, 0, 0),
                                                     (0, 0, 0, 0, 0, 0, 0),
                                                     (0, 0, 0, 0, 0, 0, 0),
                                                     (0, 2, 2, 1, 1, 2, 0),
                                                     (0, 2, 1, 2, 1, 2, 0),
                                                     (2, 1, 2, 1, 1, 1, 0),
                                                     ),
                                                    current_player=2)

    def test_search_1(self):
        actual_score = minimax(self.WINNING_BOARD, 2, focused_evaluate)
        expected_score = 1
        self.assertEqual(actual_score, expected_score)

    def test_search_2(self):
        actual_score = minimax(self.BARELY_WINNING_BOARD, 2, focused_evaluate)
        expected_score = 3
        self.assertEqual(actual_score, expected_score)

    def test_search_3(self):
        actual_score = alpha_beta_search(self.WINNING_BOARD, 2, focused_evaluate)
        expected_score = 1
        self.assertEqual(actual_score, expected_score)

    def test_search_4(self):
        actual_score = alpha_beta_search(self.BARELY_WINNING_BOARD, 2, focused_evaluate)
        expected_score = 3
        self.assertEqual(actual_score, expected_score)

    def test_search_5(self):
        actual_score = alpha_beta_search(self.WINNING_BOARD, 2, better_evaluate)
        expected_score = 1
        self.assertEqual(actual_score, expected_score)

    def test_search_6(self):
        actual_score = alpha_beta_search(self.BARELY_WINNING_BOARD, 2, better_evaluate)
        expected_score = 3
        self.assertEqual(actual_score, expected_score)


class TestConnectFourPlay(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.log = logging.getLogger("tests")

        cls.BASIC_STARTING_BOARD_1 = ConnectFourBoard(board_array=
                                                      ((0, 0, 0, 0, 0, 0, 0),
                                                       (0, 0, 0, 0, 0, 0, 0),
                                                       (0, 0, 0, 0, 0, 0, 0),
                                                       (0, 0, 0, 0, 0, 0, 0),
                                                       (0, 0, 0, 0, 0, 0, 0),
                                                       (0, 0, 1, 0, 2, 0, 0),
                                                       ),
                                                      current_player=1)

        cls.BASIC_STARTING_BOARD_2 = ConnectFourBoard(board_array=
                                                      ((0, 0, 0, 0, 0, 0, 0),
                                                       (0, 0, 0, 0, 0, 0, 0),
                                                       (0, 0, 0, 0, 0, 0, 0),
                                                       (0, 0, 0, 0, 0, 0, 0),
                                                       (0, 0, 2, 0, 0, 0, 0),
                                                       (0, 0, 1, 0, 0, 0, 0),
                                                       ),
                                                      current_player=1)

    def test_play(self):
        g1 = run_game(my_player, basic_player, self.BASIC_STARTING_BOARD_1)
        g2 = run_game(basic_player, my_player, self.BASIC_STARTING_BOARD_1)
        g3 = run_game(my_player, basic_player, self.BASIC_STARTING_BOARD_2)
        g4 = run_game(basic_player, my_player, self.BASIC_STARTING_BOARD_2)

        wins, losses = 0, 0
        if g1 == 1:
            wins += 1
        elif g1 == 2:
            losses += 1

        if g2 == 2:
            wins += 1
        elif g2 == 1:
            losses += 1

        if g3 == 1:
            wins += 1
        elif g3 == 2:
            losses += 1

        if g4 == 2:
            wins += 1
        elif g4 == 1:
            losses += 1

        return wins - losses >= 2


if __name__ == "__main__":
    logging.basicConfig(stream=sys.stderr)
    logging.getLogger("tests").setLevel(logging.DEBUG)
    unittest.main()
