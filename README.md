# linearly varying_binomial distribution calculations

```
pip install linearly-varying-binomial-distribution
```

This is a wrapper module for the previous repo: [C PROGRAM](https://github.com/cleoold/linearly_varying_binomial_distribution_calcs)

### Description of the math

Imagine the cardpool of a ptw game looks like:

One can flip a card. there is a probability (here say 0.02) to have a prize at the beginning.
* If one does not have the prize for 50 attempts in a row, the constant (here say 0.02) will be added to the existing probability (so that the chance of having the prize is increasing) until one finally has the prize, at which point the chance will reset to the original one.

For example, one tried 52 times and there have been no successes. At this point their chance for success for the 53rd time will be 0.08. If the 53-rd try is a success, then the chance for the 54-th try will be reset to 0.02, otherwise the chance becomes 0.10. Also the maximum number of tries allowed here is calculated 99, where the chance is 1.

If he tries 60 times, we can calculate the chance of getting the prize with the following code:
```py
from lvbdist import LVBdistribution
x = LVBdistribution(
    0.02, # the starting probability 
    0.02, # the constant to add
    50    # numbr of failures before triggering the addition
)
x.have_success_within_n_attempts(60) # 0.911490

```
How about the probability they just get the prize at the 60th turn
```py
x.have_first_success_at_n(60) # 0.024964
```

We can calculate the average number of attempts they need to make to have the prize:
```py
x.have_first_success_at_n_E() # 34.59455
```

We can also calculate the average successes in 60 attempts:
```py
x.have_m_successes_within_n_attempts_E(60) # 1.443428
```

Function names are self-descriptive. Note that functions ending with `_E` are expectated values. There always exist a function without the `_E` suffix.

Refer to [the lazily generated doc](https://cdn.statically.io/gh/cleoold/linearly_varying_binomial_distribution_calcs_Python/master/doc/index.html) for all functions.


### Building

Requirements: setuptools, and any modern C compiler shall work

Clone the repository:
```bash
git clone --recurse-submodules https://github.com/cleoold/linearly_varying_binomial_distribution_calcs_Python
```

You can install the package by running
```bash
make install
```

#### Developing

(Optional) set up a virtual env
```bash
python3 -m venv . # pyvenv .
source bin/activate
```

build the package in-place in the `lvbdist` folder by running
```bash
make debugging
```
And then build the distributable:
```bash
bin/pip3 install wheel
make release
```

