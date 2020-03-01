__version__ = "1.0.0"
from ._lvbdist import *


class LVBdistribution:
    '''
    Linearly varying "binomial" distribution \n
    The probability of success given some trails will increase given successive failures util it hits 1, and
    the probability will reset to base if one success occurs \n
    `base`: the starting probability to success. between 0 and 1. eg. 0.02 \n
    `additional`: the constant added to the base probability upon failures. between 0 and 1. eg 0.02 \n
    `threshold`: how many successive failures to trigger. nonnegative. eg 50
    '''
    def __init__(self,  base: float,
                        additional: float,
                        threshold: int):
        if (base < 0 or additional < 0 or threshold < 0 or
            base > 1 or additional > 1):
            raise ValueError("Invalid probability")
        if additional == 0:
            raise ValueError("Step constant cannot be 0"
                "as this will fall back to binomial distribution")
        self.base = base
        self.additional = additional
        self.threshold = threshold
        self.maxtimes = cmax_times(base, additional, threshold)
    
    def max_times_to_ensure_success(self) -> int:
        return self.maxtimes
    
    def have_success_given_no_successes_before(self, n: int) -> float:
        return chave_success_given_no_successes_before(self.base, self.additional, self.threshold, n)
    
    def have_first_sucess_at_n(self, n: int) -> float:
        return chave_first_sucess_at_n(self.base, self.additional, self.threshold, n)
    
    def have_first_sucess_at_n_E(self) -> float:
        return chave_first_sucess_at_n_E(self.base, self.additional, self.threshold)
    
    def have_success_within_n_attempts(self, n: int) -> float:
        return chave_success_within_n_attempts(self.base, self.additional, self.threshold, n)
