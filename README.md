# SQL-DB-Table
SQL Database Table written in C++

- Datalog Scanner

reads a sequence of characters from a text file, identifies the datalog language tokens found in the file, and outputs each token.

- Datalog Parser

reads a datalog program from a text file, builds a data structure that represents the datalog program, and outputs the contents of the datalog program data structure.

- The Relational Database

interpreter that uses relational database operations to evaluate the queries in a Datalog Program.

1. Evaluating Schemes

Start with an empty Database. For each scheme in the Datalog program, add an empty Relation to the Database. Use the scheme name as the name of the relation and the attribute list from the scheme as the scheme of the relation.

2. Evaluating Facts

For each fact in the Datalog program, add a Tuple to a Relation. Use the predicate name from the fact to determine the Relation to which the Tuple should be added. Use the values listed in the fact to provide the values for the Tuple.

3. Evaluating Queries

For each query in the Datalog program, use a sequence of select, project, and rename operations on the Database to evaluate the query. Evaluate the queries in the order given in the input.

- The Datalog Interpreter

Evaluate the predicates on the right-hand side of the rule:

For each predicate on the right-hand side of a rule, evaluate the predicate in the same way you evaluated the queries in the last project (using select, project, and rename operations). Each predicate should produce a single relation as an intermediate result. If there are n predicates on the right-hand side of a rule, there should be n intermediate results.

Join the relations that result:

If there are two or more predicates on the right-hand side of a rule, join the intermediate results to form the single result for Step 2. Thus, if p1, p2, and p3 are the intermediate results from Step 1, join them (p1 |x| p2 |x| p3) into a single relation.

If there is a single predicate on the right hand side of the rule, use the single intermediate result from Step 1 as the result for Step 2.

Project the columns that appear in the head predicate:

The predicates in the body of a rule may have variables that are not used in the head of the rule. The variables in the head may also appear in a different order than those in the body. Use a project operation on the result from Step 2 to remove the columns that don't appear in the head of the rule and to reorder the columns to match the order in the head.

Rename the relation to make it union-compatible:

Rename the relation that results from Step 3 to make it union compatible with the relation that matches the head of the rule. Rename each attribute in the result from Step 3 to the attribute name found in the corresponding position in the relation that matches the head of the rule.

Union with the relation in the database:

Union the result from Step 4 with the relation in the database whose name matches the name of the head of the rule.

- Optimizing Rule Evaluation
