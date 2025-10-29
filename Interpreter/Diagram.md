```mermaid
graph LR
    Term --> Result
    Term --> '*'
    Term --> '/'
    '*' --> Term2
    '/' --> Term2
    Term2 --> '*'
    Term2 --> '/'
    Term2 --> Result
    Result
```
