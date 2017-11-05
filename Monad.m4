divert(-1)
define(`lower', `translit($1, `A-Z', `a-z')')
define(`is_type_helpers',`ifelse($#, 0, , $#, 1, ,$#, 2,
`template <typename T>
struct is_'$1`_helper<$2<T>> : std::true_type {};',

`template <typename T>
struct is_$1_helper<$2<T>> : std::true_type {};

is_type_helpers($1, shift(shift($@)))')')
define(`is_monad_helper',
`template <typename T>
struct is_$1_helper : std::false_type {};

template <typename T>
struct is_$1
    : is_$1_helper<typename std::remove_reference_t<std::remove_cv_t<T>>> {};

template <typename T>
inline constexpr bool is_$1_v = is_$1<T>::value;

is_type_helpers($@)')
define(`is_monad_t', `is_monad_helper(lower($1), shift($@))')
divert(0)dnl
