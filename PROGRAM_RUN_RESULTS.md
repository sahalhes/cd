# Compiler lab: actual compilation and execution results

All 19 lab programs were compiled and executed using GCC, Flex and Yacc after the fixes. Outputs below are captured stdout/stderr; piped input is not echoed, so adjacent prompts may appear on one line. Each input block ends with a newline. These sample runs do not prove correctness for every possible input.

## 1.1 — cycle1/1_1.c

### Build

`gcc -Wall -Wextra /home/sahalhes/projects/Compiler-Design-Lab-main/cycle1/1_1.c -o program` — exit 0

### Supplied input.c

File `input.c`:
```c
// Sample C program to test lexical analyzer
int main() {
    /* Multi-line comment
       testing parser */
    int a = 10;
    int b = 20;
    if (a <= b) {
        a = a + 5;
    }
    return 0;
}
```

Actual output (exit 0):
```text
KEYWORD         : int
IDENTIFIER      : main
SPECIAL SYMBOL  : (
SPECIAL SYMBOL  : )
SPECIAL SYMBOL  : {
KEYWORD         : int
IDENTIFIER      : a
OPERATOR        : =
NUMBER          : 10
SPECIAL SYMBOL  : ;
KEYWORD         : int
IDENTIFIER      : b
OPERATOR        : =
NUMBER          : 20
SPECIAL SYMBOL  : ;
KEYWORD         : if
SPECIAL SYMBOL  : (
IDENTIFIER      : a
OPERATOR        : <=
IDENTIFIER      : b
SPECIAL SYMBOL  : )
SPECIAL SYMBOL  : {
IDENTIFIER      : a
OPERATOR        : =
IDENTIFIER      : a
OPERATOR        : +
NUMBER          : 5
SPECIAL SYMBOL  : ;
SPECIAL SYMBOL  : }
KEYWORD         : return
NUMBER          : 0
SPECIAL SYMBOL  : ;
SPECIAL SYMBOL  : }
```

### Sample file

File `input.c`:
```c
int a = 10; // ignored
a++;
```

Actual output (exit 0):
```text
KEYWORD         : int
IDENTIFIER      : a
OPERATOR        : =
NUMBER          : 10
SPECIAL SYMBOL  : ;
IDENTIFIER      : a
OPERATOR        : ++
SPECIAL SYMBOL  : ;
```

## 1.2 — cycle1/1_2.l

### Build

`flex /home/sahalhes/projects/Compiler-Design-Lab-main/cycle1/1_2.l` — exit 0

`gcc -Wall -Wextra lex.yy.c -o program` — exit 0

```text
lex.yy.c:1222:16: warning: ‘input’ defined but not used [-Wunused-function]
 1222 |     static int input  (void)
      |                ^~~~~
lex.yy.c:1179:17: warning: ‘yyunput’ defined but not used [-Wunused-function]
 1179 |     static void yyunput (int c, char * yy_bp )
      |                 ^~~~~~~
```

### Supplied input1.c

File `input1.c`:
```text
// Sample C program to test lexical analyzer
int main() {
    /* Multi-line comment
       testing parser */
    int a = 10;
    int b = 20;
    if (a <= b) {
        a = a + 5;
    }
    return 0;
}
```

Actual output (exit 0):
```text
KEYWORD         : int
IDENTIFIER      : main
SPECIAL SYMBOL  : (
SPECIAL SYMBOL  : )
SPECIAL SYMBOL  : {
KEYWORD         : int
IDENTIFIER      : a
OPERATOR        : =
NUMBER          : 10
SPECIAL SYMBOL  : ;
KEYWORD         : int
IDENTIFIER      : b
OPERATOR        : =
NUMBER          : 20
SPECIAL SYMBOL  : ;
KEYWORD         : if
SPECIAL SYMBOL  : (
IDENTIFIER      : a
OPERATOR        : <=
IDENTIFIER      : b
SPECIAL SYMBOL  : )
SPECIAL SYMBOL  : {
IDENTIFIER      : a
OPERATOR        : =
IDENTIFIER      : a
OPERATOR        : +
NUMBER          : 5
SPECIAL SYMBOL  : ;
SPECIAL SYMBOL  : }
KEYWORD         : return
NUMBER          : 0
SPECIAL SYMBOL  : ;
SPECIAL SYMBOL  : }

--- Token Counts ---
Keywords        : 5
Identifiers     : 7
Numbers         : 4
Operators       : 5
Special Symbols : 12
```

## 1.3 — cycle1/1_3.l

### Build

`flex /home/sahalhes/projects/Compiler-Design-Lab-main/cycle1/1_3.l` — exit 0

`gcc -Wall -Wextra lex.yy.c -o program` — exit 0

```text
lex.yy.c:1129:16: warning: ‘input’ defined but not used [-Wunused-function]
 1129 |     static int input  (void)
      |                ^~~~~
lex.yy.c:1086:17: warning: ‘yyunput’ defined but not used [-Wunused-function]
 1086 |     static void yyunput (int c, char * yy_bp )
      |                 ^~~~~~~
```

### Supplied input2.c

File `input2.c`:
```text
Hello World
This is a test
Lex program
```

Actual output (exit 0):
```text

--- Result ---
Lines        : 3
Words        : 8
Characters   : 39
```

## 1.4 — cycle1/1_4.l

### Build

`flex /home/sahalhes/projects/Compiler-Design-Lab-main/cycle1/1_4.l` — exit 0

`gcc -Wall -Wextra lex.yy.c -o program` — exit 0

```text
lex.yy.c:1127:16: warning: ‘input’ defined but not used [-Wunused-function]
 1127 |     static int input  (void)
      |                ^~~~~
lex.yy.c:1084:17: warning: ‘yyunput’ defined but not used [-Wunused-function]
 1084 |     static void yyunput (int c, char * yy_bp )
      |                 ^~~~~~~
```

### Replacement

Input:
```text
abc xyz abcabc
```

Actual output (exit 0):
```text
Enter input: ABC xyz ABCABC
```

## 1.5 — cycle1/1_5.l

### Build

`flex /home/sahalhes/projects/Compiler-Design-Lab-main/cycle1/1_5.l` — exit 0

`gcc -Wall -Wextra lex.yy.c -o program` — exit 0

```text
lex.yy.c:1131:16: warning: ‘input’ defined but not used [-Wunused-function]
 1131 |     static int input  (void)
      |                ^~~~~
lex.yy.c:1088:17: warning: ‘yyunput’ defined but not used [-Wunused-function]
 1088 |     static void yyunput (int c, char * yy_bp )
      |                 ^~~~~~~
```

### Letter counts

Input:
```text
Hello World!
```

Actual output (exit 0):
```text
Enter input: 
--- Result ---
Vowels       : 3
Consonants   : 7
```

## 2.1 — cycle2/2_1.l

### Build

`yacc -d /home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_1.y` — exit 0

`flex /home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_1.l` — exit 0

`gcc -Wall -Wextra y.tab.c lex.yy.c -o program` — exit 0

```text
/home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_1.y: In function ‘yyerror’:
/home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_1.y:38:20: warning: unused parameter ‘s’ [-Wunused-parameter]
   38 | void yyerror(char *s) {
      |              ~~~~~~^
lex.yy.c:1143:16: warning: ‘input’ defined but not used [-Wunused-function]
 1143 |     static int input  (void)
      |                ^~~~~
lex.yy.c:1100:17: warning: ‘yyunput’ defined but not used [-Wunused-function]
 1100 |     static void yyunput (int c, char * yy_bp )
      |                 ^~~~~~~
```

### Valid sample

Input:
```text
a+3*(b-2)
```

Actual output (exit 0):
```text
Enter expression: Valid Expression
```

### Invalid sample

Input:
```text
a+*b
```

Actual output (exit 0):
```text
Enter expression: Invalid Expression
```

## 2.2 — cycle2/2_2.l

### Build

`yacc -d /home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_2.y` — exit 0

`flex /home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_2.l` — exit 0

`gcc -Wall -Wextra y.tab.c lex.yy.c -o program` — exit 0

```text
/home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_2.y: In function ‘yyerror’:
/home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_2.y:24:20: warning: unused parameter ‘s’ [-Wunused-parameter]
   24 | void yyerror(char *s) {
      |              ~~~~~~^
lex.yy.c:1130:16: warning: ‘input’ defined but not used [-Wunused-function]
 1130 |     static int input  (void)
      |                ^~~~~
lex.yy.c:1087:17: warning: ‘yyunput’ defined but not used [-Wunused-function]
 1087 |     static void yyunput (int c, char * yy_bp )
      |                 ^~~~~~~
```

### Valid sample

Input:
```text
abc123
```

Actual output (exit 0):
```text
Enter identifier: Valid Identifier
```

### Invalid sample

Input:
```text
1abc
```

Actual output (exit 0):
```text
Enter identifier: Invalid Identifier
```

### Leading underscore rejected

Input:
```text
_abc
```

Actual output (exit 0):
```text
Enter identifier: Invalid Identifier
```

## 2.3 — cycle2/2_3.l

### Build

`yacc -d /home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_3.y` — exit 0

`flex /home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_3.l` — exit 0

`gcc -Wall -Wextra y.tab.c lex.yy.c -o program` — exit 0

```text
/home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_3.y: In function ‘yyerror’:
/home/sahalhes/projects/Compiler-Design-Lab-main/cycle2/2_3.y:36:20: warning: unused parameter ‘s’ [-Wunused-parameter]
   36 | void yyerror(char *s) {
      |              ~~~~~~^
lex.yy.c:1139:16: warning: ‘input’ defined but not used [-Wunused-function]
 1139 |     static int input  (void)
      |                ^~~~~
lex.yy.c:1096:17: warning: ‘yyunput’ defined but not used [-Wunused-function]
 1096 |     static void yyunput (int c, char * yy_bp )
      |                 ^~~~~~~
```

### Valid sample

Input:
```text
(10+2)*3-8/2
```

Actual output (exit 0):
```text
Enter expression: Result = 32
```

### Invalid sample

Input:
```text
2+*3
```

Actual output (exit 0):
```text
Enter expression: Invalid Expression
```

### Division by zero

Input:
```text
5/0
```

Actual output (exit 0):
```text
Enter expression: Error: division by zero
```

## 3.1 — cycle3/3_1.l

### Build

`yacc -d /home/sahalhes/projects/Compiler-Design-Lab-main/cycle3/3_1.y` — exit 0

`flex /home/sahalhes/projects/Compiler-Design-Lab-main/cycle3/3_1.l` — exit 0

`gcc -Wall -Wextra y.tab.c lex.yy.c -o program` — exit 0

```text
/home/sahalhes/projects/Compiler-Design-Lab-main/cycle3/3_1.y: In function ‘yyerror’:
/home/sahalhes/projects/Compiler-Design-Lab-main/cycle3/3_1.y:89:19: warning: unused parameter ‘s’ [-Wunused-parameter]
   89 | void yyerror(char s[10]) {
      |              ~~~~~^~~~~
lex.yy.c:1147:16: warning: ‘input’ defined but not used [-Wunused-function]
 1147 |     static int input  (void)
      |                ^~~~~
lex.yy.c:1104:17: warning: ‘yyunput’ defined but not used [-Wunused-function]
 1104 |     static void yyunput (int c, char * yy_bp )
      |                 ^~~~~~~
```

### Valid sample

Input:
```text
a+b*c
```

Actual output (exit 0):
```text
Enter expression to construct AST (e.g. a+b*c): 
--- Abstract Syntax Tree (Indented Format) ---
+
   a
   *
      b
      c

AST Pre-order Traversal (Prefix): + a * b c
```

### Invalid sample

Input:
```text
a+*b
```

Actual output (exit 0):
```text
Enter expression to construct AST (e.g. a+b*c): Invalid Expression for AST
```

## 3.2 — cycle3/3_2.c

### Build

`gcc -Wall -Wextra /home/sahalhes/projects/Compiler-Design-Lab-main/cycle3/3_2.c -o program` — exit 0

### Epsilon closure

Input:
```text
3
- e -
- - a
- - -
```

Actual output (exit 0):
```text
Enter number of states: 
Enter transitions ('e' for epsilon, '-' for none):
q0 to q0: q0 to q1: q0 to q2: q1 to q0: q1 to q1: q1 to q2: q2 to q0: q2 to q1: q2 to q2: 
--- Epsilon Closures ---
e-closure(q0) = { q0, q1 }
e-closure(q1) = { q1 }
e-closure(q2) = { q2 }
```

## 3.3 — cycle3/3_3.c

### Build

`gcc -Wall -Wextra /home/sahalhes/projects/Compiler-Design-Lab-main/cycle3/3_3.c -o program` — exit 0

### Epsilon removal

Input:
```text
3
- e -
- - a
- - -
1
2
```

Actual output (exit 0):
```text
Enter number of states: 
Enter transitions ('e' for epsilon, '-' for none):
q0 to q0: q0 to q1: q0 to q2: q1 to q0: q1 to q1: q1 to q2: q2 to q0: q2 to q1: q2 to q2: 
--- Epsilon Closures ---
e-closure(q0) = { q0, q1 }
e-closure(q1) = { q1 }
e-closure(q2) = { q2 }

--- NFA Without Epsilon Transitions ---
q0 on 'a' -> q2
q1 on 'a' -> q2
Enter number of final states: Enter final states: New final states: q2 
Start state: q0
```

### Epsilon after symbol

Input:
```text
3
- a -
- - e
- - -
1
2
```

Actual output (exit 0):
```text
Enter number of states: 
Enter transitions ('e' for epsilon, '-' for none):
q0 to q0: q0 to q1: q0 to q2: q1 to q0: q1 to q1: q1 to q2: q2 to q0: q2 to q1: q2 to q2: 
--- Epsilon Closures ---
e-closure(q0) = { q0 }
e-closure(q1) = { q1, q2 }
e-closure(q2) = { q2 }

--- NFA Without Epsilon Transitions ---
q0 on 'a' -> q1
q0 on 'a' -> q2
Enter number of final states: Enter final states: New final states: q1 q2 
Start state: q0
```

## 3.4 — cycle3/3_4.c

### Build

`gcc -Wall -Wextra /home/sahalhes/projects/Compiler-Design-Lab-main/cycle3/3_4.c -o program` — exit 0

### Subset construction

Input:
```text
2
2
a b
2 0 1
0
0
1 1
1
1
```

Actual output (exit 0):
```text
Enter number of states: Enter number of input symbols: Enter input symbols (e.g. a b): 
Enter transitions for each state:
Transitions from q0 on 'a' (count):   Enter destination states: Transitions from q0 on 'b' (count): Transitions from q1 on 'a' (count): Transitions from q1 on 'b' (count):   Enter destination states: Enter number of final states: Enter final states: 
--- Resulting DFA Transition Table ---
State	Subset		a	b	
---------------------------------------------
q0	{ 0 }		q1	q2	
q1	{ 0 1 }		q1	q3	
q2	{ }		q2	q2	
q3	{ 1 }		q2	q3	
Start state: q0
Final DFA states: q1 q3
```

## 3.5 — cycle3/3_5.c

### Build

`gcc -Wall -Wextra /home/sahalhes/projects/Compiler-Design-Lab-main/cycle3/3_5.c -o program` — exit 0

### Equivalent states and unreachable state

Input:
```text
4
2
a b
1 2
1 2
1 2
3 3
2
1 2
```

Actual output (exit 0):
```text
Enter number of states: Enter number of input symbols: Enter input symbols (e.g. a b): 
Enter transition table:
  State q0 on 'a' -> q  State q0 on 'b' -> q  State q1 on 'a' -> q  State q1 on 'b' -> q  State q2 on 'a' -> q  State q2 on 'b' -> q  State q3 on 'a' -> q  State q3 on 'b' -> q
Enter number of final states: Enter final states (e.g. 2 3): 
--- Equivalent State Groups ---
Group Q0 = { q0 }
Group Q1 = { q1 q2 }

--- Minimized DFA Transition Table ---
State	a	b	Final State?
Q0	Q1	Q1	No
Q1	Q1	Q1	Yes

Start State: Q0
```

## 4.1 — cycle4/4_1.c

### Build

`gcc -Wall -Wextra /home/sahalhes/projects/Compiler-Design-Lab-main/cycle4/4_1.c -o program` — exit 0

### Simple grammar

Input:
```text
3
S->AB
A->a
B->b
```

Actual output (exit 0):
```text
Enter the number of productions: Enter productions (one alternative per line, e for epsilon):

--- FIRST and FOLLOW Sets ---
FIRST(A)  : { a }
FOLLOW(A) : { b }

FIRST(B)  : { b }
FOLLOW(B) : { $ }

FIRST(S)  : { a }
FOLLOW(S) : { $ }
```

### Nullable grammar

Input:
```text
4
S->AB
A->a
A->e
B->b
```

Actual output (exit 0):
```text
Enter the number of productions: Enter productions (one alternative per line, e for epsilon):

--- FIRST and FOLLOW Sets ---
FIRST(A)  : { a e }
FOLLOW(A) : { b }

FIRST(B)  : { b }
FOLLOW(B) : { $ }

FIRST(S)  : { a b }
FOLLOW(S) : { $ }
```

### Nullable suffix FOLLOW

Input:
```text
4
S->AB
A->a
B->b
B->e
```

Actual output (exit 0):
```text
Enter the number of productions: Enter productions (one alternative per line, e for epsilon):

--- FIRST and FOLLOW Sets ---
FIRST(A)  : { a }
FOLLOW(A) : { $ b }

FIRST(B)  : { b e }
FOLLOW(B) : { $ }

FIRST(S)  : { a }
FOLLOW(S) : { $ }
```

### Left recursive grammar

Input:
```text
2
E->E+a
E->a
```

Actual output (exit 0):
```text
Enter the number of productions: Enter productions (one alternative per line, e for epsilon):

--- FIRST and FOLLOW Sets ---
FIRST(E)  : { a }
FOLLOW(E) : { $ + }
```

## 4.2 — cycle4/4_2.c

### Build

`gcc -Wall -Wextra /home/sahalhes/projects/Compiler-Design-Lab-main/cycle4/4_2.c -o program` — exit 0

### Valid sample

Input:
```text
i+i*i
```

Actual output (exit 0):
```text
Enter the input string: 
i+i*i                E -> T E'
i+i*i                T -> F T'
i+i*i                F -> i
+i*i                 T' -> e
+i*i                 E' -> + T E'
i*i                  T -> F T'
i*i                  F -> i
*i                   T' -> * F T'
i                    F -> i
                     T' -> e
                     E' -> e

String Accepted
```

### Invalid sample

Input:
```text
i+*i
```

Actual output (exit 0):
```text
Enter the input string: 
i+*i                 E -> T E'
i+*i                 T -> F T'
i+*i                 F -> i
+*i                  T' -> e
+*i                  E' -> + T E'
*i                   T -> F T'

String Rejected
```

## 4.3 — cycle4/4_3.c

### Build

`gcc -Wall -Wextra /home/sahalhes/projects/Compiler-Design-Lab-main/cycle4/4_3.c -o program` — exit 0

### Valid sample

Input:
```text
i+i*i
```

Actual output (exit 0):
```text
Enter input string: 
Stack		Input			Action
i		+i*i                 SHIFT
E		+i*i                 REDUCE: E -> i
E+		i*i                  SHIFT
E+i		*i                   SHIFT
E+E		*i                   REDUCE: E -> i
E+E*		i                    SHIFT
E+E*i		                     SHIFT
E+E*E		                     REDUCE: E -> i
E+E		                     REDUCE: E -> E*E
E		                     REDUCE: E -> E+E

String Accepted
```

### Invalid sample

Input:
```text
i+*i
```

Actual output (exit 0):
```text
Enter input string: 
Stack		Input			Action
i		+*i                  SHIFT
E		+*i                  REDUCE: E -> i
E+		*i                   SHIFT
E+*		i                    SHIFT
E+*i		                     SHIFT
E+*E		                     REDUCE: E -> i

String Rejected
```

## 5.1 — cycle5/5_1.c

### Build

`gcc -Wall -Wextra /home/sahalhes/projects/Compiler-Design-Lab-main/cycle5/5_1.c -o program` — exit 0

### Constant propagation

Input:
```text
4
a=5
b=a+3
c=b*2
d=x+2
```

Actual output (exit 0):
```text
Enter number of statements: Enter statements (e.g. a=5, b=a+3, c=b*2):
Statement 1: Result: a = 5
Statement 2: Result: b = 5 + 3 = 8
Statement 3: Result: c = 8 * 2 = 16
Statement 4: Result: d = x + 2
```

### Division by zero

Input:
```text
1
a=5/0
```

Actual output (exit 0):
```text
Enter number of statements: Enter statements (e.g. a=5, b=a+3, c=b*2):
Statement 1: Error: division by zero
```

## 5.2 — cycle5/5_2.c

### Build

`gcc -Wall -Wextra /home/sahalhes/projects/Compiler-Design-Lab-main/cycle5/5_2.c -o program` — exit 0

### Intermediate code

Input:
```text
a=b+c*d
```

Actual output (exit 0):
```text
Enter expression (e.g. a=b+c*d): 
Op	Dest	Arg1	Arg2		Three Address Code
*	t1	c	d		t1 = c * d
+	t2	b	t1		t2 = b + t1
=	a	t2	-		a = t2
```

### Equal precedence associativity

Input:
```text
a=b-c+d
```

Actual output (exit 0):
```text
Enter expression (e.g. a=b+c*d): 
Op	Dest	Arg1	Arg2		Three Address Code
-	t1	b	c		t1 = b - c
+	t2	t1	d		t2 = t1 + d
=	a	t2	-		a = t2
```

### Repeated operators

Input:
```text
a=b+c+d
```

Actual output (exit 0):
```text
Enter expression (e.g. a=b+c*d): 
Op	Dest	Arg1	Arg2		Three Address Code
+	t1	b	c		t1 = b + c
+	t2	t1	d		t2 = t1 + d
=	a	t2	-		a = t2
```

## 5.3 — cycle5/5_3.c

### Build

`gcc -Wall -Wextra /home/sahalhes/projects/Compiler-Design-Lab-main/cycle5/5_3.c -o program` — exit 0

### Assembly output

Input:
```text
a=b+c
d=a-b
e=b*c
f=c/b
g=a
exit
```

Actual output (exit 0):
```text
Enter set of Three-Address Code statements (type 'exit' to end):
Statement 1: Statement 2: Statement 3: Statement 4: Statement 5: Statement 6: 
--- Generated 8086 Assembly Code ---

; Translation of: a=b+c
MOV AX, b
ADD AX, c
MOV a, AX

; Translation of: d=a-b
MOV AX, a
SUB AX, b
MOV d, AX

; Translation of: e=b*c
MOV AX, b
MOV BX, c
IMUL BX
MOV e, AX

; Translation of: f=c/b
MOV AX, c
CWD
MOV BX, b
IDIV BX
MOV f, AX

; Translation of: g=a
MOV AX, a
MOV g, AX
```

## Other C files

`cycle1/input1.c` and `cycle1/input2.c` are lexer input data, not additional lab programs. `cycle3/sample.c` is a sample C input; it was also compiled separately:
```text
/home/sahalhes/projects/Compiler-Design-Lab-main/cycle3/sample.c:1:1: warning: return type defaults to ‘int’ [-Wimplicit-int]
    1 | main() {
      | ^~~~
```

Sample executable exit: 0. It produces no output.
