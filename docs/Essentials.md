# Important
- All getter/setter methods are just `get`or `set` before the arg used in CamelCase
- Comments/Explanations can be found in `docs/` for each class
- If unable to understand a concept, do check `extras.md` in `docs/` before posting.

# Ideology
- Naming conventions are quite mixed throughout the codebase. CamelCase, SnakeCase, etc..


# Optimizations
- `const` has been used wherever possible as some compilers do optimizations for them & also it's good as it prevents unintended changes.
- `inline` for small methods/functions.

# Notes
- `base.cpp` contains the important functions doing basic functionality (not an algo) whereas, the `algos_base.cpp` file contains the basic algos which sometimes use the functions from `base.cpp`.