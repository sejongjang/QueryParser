# SQL-DB-Table
SQL Database Table written in C++

- Datalog Scanner
reads a sequence of characters from a text file, identifies the datalog language tokens found in the file, and outputs each token.

- Datalog Parser
reads a datalog program from a text file, builds a data structure that represents the datalog program, and outputs the contents of the datalog program data structure.

- The Relational Database
interpreter that uses relational database operations to evaluate the queries in a Datalog Program.
Evaluating Schemes
Start with an empty Database. For each scheme in the Datalog program, add an empty Relation to the Database. Use the scheme name as the name of the relation and the attribute list from the scheme as the scheme of the relation.

Evaluating Facts
For each fact in the Datalog program, add a Tuple to a Relation. Use the predicate name from the fact to determine the Relation to which the Tuple should be added. Use the values listed in the fact to provide the values for the Tuple.

Evaluating Queries
For each query in the Datalog program, use a sequence of select, project, and rename operations on the Database to evaluate the query. Evaluate the queries in the order given in the input.

- The Datalog Interpreter
- Optimizing Rule Evaluation
