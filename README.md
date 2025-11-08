# JSON Parser
## Documentation
```c
int JP_find_str(char buffer_json[], char key[]);
```
Mostly for inner purpose, but decided to not do it 'static' for now, just in case.  

```c
char *JP_get_value(char buffer_json[], char key[]);
```
Main function for getting value by key.
