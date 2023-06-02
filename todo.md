# TODO Ideas

* Add support for more generic and "automatic" token addition
* Support for string literals
* Support for numerical bases (hex, oct, bin, dec)
* Support for comments
* Generalize the lexer so it can be used on the REPL
* Create a "SourceStream" generator class
* Support for multiple errors (do not stop at first error?)

## Tests

* Add grouped expression test
* Add boolean literal test
* Check expression of let and return tests
* Add if expressison tests

* Use std::list whenever possible


Int
Bool
Float
String
Identifier

Literals:
    Boolean -> <Bool>
    String -> <String>
    Array -> <LBracket>[<Expression>, ...]<RBracket>
    Hash -> <LSquirly>[(<Identifier> | (<LBracket><String><RBracket>))<Colon><Expression>, ...]<RSquirly>
    Int -> <Int>

Expressions:
    Prefix:
        Function -> <"fn"><LParen>[<Identifier>, ...]<RParen><LSquirly><Block><RSquirly>
        Grouped -> <LParen><Expression><RParen>
        While -> <"while"><LParen><Expression><RParen><LSquirly><Block><RSquirly>
        Minus -> <Minus><Expression>
        Not -> (<Not> | <Bang>)<Expression>
        For -> <"for"><LParen>[(<LetStatement> | <AssignmentExpression>)]<SemiColon>[<Expression>]<Semicolon>[<Expression>]<RParen>
        If -> <"if"><LParen>[<Expression>]<RParen><LSquirly><Block><RSquirly>[<"else"><LSquirly><Block><RSquirly>]
    Infix:
        Assign -> <Identifier><Assign><Expression>
        Index -> <Identifier><LBracket><Expression><RBracket>
        Minus -> <Expression><Minus><Expression>
        Call -> (<Identifier> | <FunctionLiteral>)<LParen>[<Expression>, ...]<RParen>
        Plus -> <Expression><Plus><Expression>
        Mod -> <Expression><Mod><Expression>
        Div -> <
        Mul ->
        And ->
        Eq ->
        Ne ->
        Or ->
        Lt ->
        Gt ->
