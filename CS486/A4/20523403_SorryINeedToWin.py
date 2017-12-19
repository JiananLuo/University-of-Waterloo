from prison import Player
import random

class SorryINeedToWin(Player):
    """
    j43luo agent
    """
        
    def studentID(self):
        return "20523403"
    def agentName(self):
        return "SorryINeedToWin"
    def play(self, myHistory, oppHistory1, oppHistory2):
        # base case, be a nice player in the beginning
        if len(oppHistory1) == 0:
            return 0
        # find most recent 10 rounds, if more than 10, count as 10
        rounds = min(10, len(oppHistory1))
        # find number defected of oppoent 1 & 2 in the most recent 10 rounds
        num_of_op1_defect_last_ten_result = sum(oppHistory1[-10:])
        num_of_op2_defect_last_ten_result = sum(oppHistory2[-10:])
        # find number cooperates of oppoent 1 & 2 in the most recent 10 rounds
        num_of_op1_cooperates_last_ten_result = rounds - num_of_op1_defect_last_ten_result
        num_of_op2_cooperates_last_ten_result = rounds - num_of_op2_defect_last_ten_result
        # find opponent 1 & 2 true behavior with noisy factor
        op1_result_with_noisy_factor = (num_of_op1_defect_last_ten_result * 0.98 + num_of_op1_cooperates_last_ten_result * 0.02) / rounds
        op2_result_with_noisy_factor = (num_of_op2_defect_last_ten_result * 0.98 + num_of_op2_cooperates_last_ten_result * 0.02) / rounds
        # find the defect probability of oppoent 1 & 2
        op1_prob_of_defect = op1_result_with_noisy_factor / rounds
        op2_prob_of_defect = op2_result_with_noisy_factor / rounds
        # find the max defect probability of oppoent 1 & 2
        max_prob_of_defect = max(op1_prob_of_defect, op2_prob_of_defect)

        if random.random() < max_prob_of_defect:
            return 1
        else:
            return 0
