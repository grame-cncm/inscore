%%
stmt:
  number
  stmt number
| op
;
op:
  "-" number
 | number "- " number
 | "a"
 | "a" "a"
;
number:
  "0"
;
