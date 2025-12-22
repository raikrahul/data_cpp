
01. ERROR: s.type() called on std::variant
    WRONG: std::variant has .type() method
    RIGHT: std::variant has .index() only, returns size_t {0,1,2...}
    ORTHOGONAL: C union has no type info, variant stores index, not type name
    FIX: s.index() → 0, 1, 2 | typeid requires get<T>(s) first

02. ERROR: "templates not allowed inside lambda"
    WRONG: [](auto x) cannot use template features
    RIGHT: [](auto x) = template<T> operator()(T x) in disguise
    ORTHOGONAL: lambda = compiler-generated struct with operator()
    FIX: auto parameter = implicit template, all template tools work

03. ERROR: "if constexpr needs constexpr loop/literal"
    WRONG: if constexpr only works with constexpr int x = 5
    RIGHT: if constexpr works with any compile-time bool
    ORTHOGONAL: is_same_v<T,U> = compile-time bool, types never change at runtime
    FIX: T = fixed at template instantiation → is_same_v<T,X> = constexpr

04. ERROR: "x = {1,2} should work on variant"
    WRONG: variant can hold multiple values like container
    RIGHT: variant = union + tag, holds ONE value at a time
    ORTHOGONAL: {1,2} = aggregate init, needs struct/array, int/double are scalars
    FIX: variant<pair<int,int>,double> x = make_pair(1,2); OR vector

05. ERROR: "{}" syntax inside function call unknown
    WRONG: func(Type{}) is invalid syntax
    RIGHT: Type{} = temporary object, valid anywhere expression expected
    ORTHOGONAL: Type v; func(v); = named | func(Type{}); = temporary
    FIX: Type{} = Type() = default-constructed temporary

06. ERROR: "operator() with multiple types overloaded never seen"
    WRONG: operator() can only have one signature
    RIGHT: operator() can have N overloads like any function
    ORTHOGONAL: struct with operator() = functor = callable object
    FIX: visitor pattern = struct with operator()(T) for each T in variant

07. PATTERN: Assumed std::variant = std::vector-like container
    WRONG: variant stores multiple values
    RIGHT: variant stores ONE value, tracks which TYPE is active
    ORTHOGONAL: vector = same type, many values | variant = many types, one value

08. PATTERN: Confused compile-time vs runtime
    WRONG: if constexpr = runtime if with constexpr values
    RIGHT: if constexpr = compile-time branch elimination
    ORTHOGONAL: regular if compiles both branches | if constexpr discards false branch

09. PATTERN: Never saw temporary object syntax
    WRONG: objects must be named before use
    RIGHT: Type{} creates unnamed temporary, dies after expression
    ORTHOGONAL: named lasts until scope | temporary lasts until statement end

10. QUESTION: decay_t confusion
    ASKED: what is decay_t?
    ANSWER: decay_t removes &, &&, const, volatile from type
    ORTHOGONAL: is_same<int&, int> = false | is_same<decay_t<int&>, int> = true

11. QUESTION: auto&& confusion
    ASKED: what is &&?
    ANSWER: auto&& = forwarding reference, accepts lvalue or rvalue
    ORTHOGONAL: auto& = lvalue only | auto&& = both | auto = copy

BRAIN PATTERNS IDENTIFIED:
├── Assumed syntax unknown = syntax invalid
├── Assumed one overload per function
├── Confused container (many values) with variant (one value)
├── Skipped compile-time vs runtime distinction
└── Never traced temporary object lifetimes

FIXES FOR BRAIN:
├── Unknown syntax → try compiler → read error → learn
├── operator() = function → can have N overloads
├── variant = discriminated union = one slot, type tag
├── constexpr = compile-time, template = compile-time, types = compile-time
└── {} after Type = temporary, dies at semicolon
