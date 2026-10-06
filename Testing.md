# Testing Record

## Student 7
**Name:** Othello Joseph  
**Responsibility:** Testing, documentation and Git coordination

## Testing performed

| # | Test | Expected result | Result |
|---|---|---|---|
| 1 | Main menu options 1-6 | Correct module opens / system exits | PASS |
| 2 | Invalid main-menu input (e.g. 0, 99, text) | Invalid input is rejected | PASS |
| 3 | Add employee | Employee is stored and displayed | PASS |
| 4 | Employee search | Existing ID is found; missing ID reports not found | PASS |
| 5 | Employee salary calculation | Basic + housing + transport is calculated | PASS |
| 6 | Negative employee salary/allowances | Negative values are rejected | PASS |
| 7 | Add department budget | Budget is stored | PASS |
| 8 | Enter expenditure | Expenditure is stored for the selected department | PASS |
| 9 | Remaining/over-budget calculation | Correct balance and status are shown | PASS |
| 10 | Supplier validation | Invalid email/telephone is rejected | PASS |
| 11 | Asset validation | Negative purchase value is rejected | PASS |
| 12 | Reports menu | Employee, budget, supplier and asset reports open correctly | PASS |

## Issue found and fixed

During testing, the Employee and Budget modules used `scanf()` while the rest of the program used the shared validation functions in `input.c`. This caused input-buffer/menu problems and weaker validation after returning between modules.

The Employee and Budget modules were updated to use the shared `readInt()`, `readFloat()` and `readString()` functions consistently. This also prevents negative salary, allowance, budget and expenditure values and handles invalid numeric input more reliably.

## Evidence
The test cases above were executed against the compiled project. The repository should retain the commit history showing the testing/validation changes and documentation updates.
