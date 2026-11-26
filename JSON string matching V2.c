#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stack element: stores the bracket type ({ / } / [ / ]) and its index (for error location)
typedef struct {
    char bracket;  // Bracket character
    int position;  // Position of the bracket in the JSON string (0-based)
} StackElem;

// Stack structure (grows dynamically to avoid a fixed capacity limit)
typedef struct {
    StackElem* data;     // Stack data array
    int top;             // Top index (-1 means the stack is empty)
    int capacity;        // Current capacity
    int max_capacity;    // Maximum capacity
} Stack;

// Stack operation result enum (for robustness)
typedef enum {
    STACK_OK,           // Operation succeeded
    STACK_EMPTY,        // Stack is empty (pop/peek failed)
    STACK_FULL,         // Stack is full (push failed)
    STACK_MEM_ERR       // Memory allocation failed
} StackResult;

// ---------------------------- Student stack interface to implement ----------------------------
// 1. Initialize the stack (with an initial capacity and a maximum capacity)
StackResult stackInit(Stack* stack, int init_capacity, int max_capacity){
    // Student implementation:
    // Step 1: validate init_capacity and max_capacity (init <= max, both > 0)
    if(init_capacity <= 0 || max_capacity <= 0 || init_capacity > max_capacity) {
        return STACK_MEM_ERR; // Invalid capacity
    }
    // Step 2: allocate memory for stack->data (malloc)
    stack->data = (StackElem*)malloc(sizeof(StackElem) * init_capacity);
    if(stack->data == NULL) {
        return STACK_MEM_ERR; // Memory allocation failed
    }
    // Step 3: set top = -1, capacity = init_capacity, max_capacity = max_capacity
    stack->top = -1;
    stack->capacity = init_capacity;
    stack->max_capacity = max_capacity;
    // Step 4: return the corresponding result (STACK_OK / STACK_MEM_ERR)
    return STACK_OK;
}

// 2. Push (store data on the stack)
StackResult stackPush(Stack* stack, char bracket, int position){
        // Student implementation:
    // Step 1: check whether the stack is full (top + 1 == capacity); if so, try to grow it (not beyond max_capacity)
    if(stack->top + 1 >= stack->capacity) {
        // Compute the new capacity (usually 2x the old one, capped at max_capacity)
        int new_capacity = stack->capacity * 2;
        if(new_capacity > stack->max_capacity) {
            new_capacity = stack->max_capacity;
        }
        if(new_capacity <= stack->capacity) {
            return STACK_FULL; // Cannot grow
        }
        // Try to grow
        StackElem* new_data = (StackElem*)realloc(stack->data, sizeof(StackElem) * new_capacity);
        if(new_data == NULL) {
            return STACK_MEM_ERR; // Memory allocation failed
        }
        stack->data = new_data;
        stack->capacity = new_capacity;
    }
    // Step 2: return STACK_FULL if growing failed; otherwise the capacity is updated
    if(stack->top + 1 >= stack->capacity) {
        return STACK_FULL; // Still full after growing
    }
    // Step 3: increment the top index and store bracket and position
    stack->top++;
    stack->data[stack->top].bracket = bracket;
    stack->data[stack->top].position = position;
    // Step 4: return STACK_OK
    return STACK_OK;
}

// 3. Pop (take the top element and return it through elem)
StackResult stackPop(Stack* stack, StackElem* elem){
    // Student implementation:
    // Step 1: check whether the stack is empty (stackIsEmpty); if so return STACK_EMPTY
    if(stackIsEmpty(stack)) {
        return STACK_EMPTY;
    }
    // Step 2: copy the top element into elem (bracket and position)
    *elem = stack->data[stack->top];
    // Step 3: decrement the top index
    stack->top--;
    // Step 4: return STACK_OK
    return STACK_OK;
}
// 4. Peek the top
StackResult stackPeek(Stack* stack, StackElem* elem) {
    // Student implementation:
    // Step 1: check whether the stack is empty (stackIsEmpty); if so return STACK_EMPTY
    if(stackIsEmpty(stack)) {
        return STACK_EMPTY;
    }
    // Step 2: copy the top element into elem (bracket and position)
    *elem = stack->data[stack->top];
    // Step 3: return STACK_OK
    return STACK_OK;
}

// 5. Emptiness check (1 = empty, 0 = not empty)
int stackIsEmpty(const Stack* stack){
    // Student implementation: return stack->top == -1 ? 1 : 0
    return stack->top == -1 ? 1 : 0;
}

// 6. Destroy the stack (free memory)
void stackDestroy(Stack* stack) {
    // Student implementation: free stack->data; reset top = -1 and capacity = 0
    free(stack->data);
    stack->top = -1;
    stack->capacity = 0;
}


// Helper functions
// Check whether it is a left bracket
int isLeftBracket(char ch) {
    return ch == '{' || ch == '[';
}
// Check whether it is a right bracket
int isRightBracket(char ch) {
    return ch == '}' || ch == ']';
}
// Check whether the brackets match
int isBracketMatch(char left, char right) {
    return (left == '{' && right == '}') || (left == '[' && right == ']');
}


// Basic stack version
int jsonBracketCheckBasic(const char *json_str) {
    // Student implementation:
    // Step 1: handle edge cases (json_str is NULL or an empty string: return 1)
    if(json_str == NULL || strlen(json_str) == 0) {
        return 1; // An empty string counts as valid
    }
    // Step 2: initialize the stack (call stackInit)
    Stack stack;
    if(stackInit(&stack, 10, 100) != STACK_OK) {
        return 0; // Initialization failed, treat as invalid
    }
    // Step 3: walk through each character of json_str:
    //        - Left bracket ({ / [): push (stackPush)
    //        - Right bracket (} / ]): pop and check the match (isBracketMatch); return 0 on a mismatch
    //        - Other characters (letters, digits, quotes): skip
    for(int i = 0; json_str[i] != '\0'; i++) {
        char ch = json_str[i];
        if(isLeftBracket(ch)) {
            if(stackPush(&stack, ch, i) != STACK_OK) {
                stackDestroy(&stack);
                return 0; // Push failed, treat as invalid
            }
        } else if(isRightBracket(ch)) {
            StackElem topElem;
            if(stackPop(&stack, &topElem) != STACK_OK) {
                stackDestroy(&stack);
                return 0; // Pop failed: extra right bracket
            }
            if(!isBracketMatch(topElem.bracket, ch)) {
                stackDestroy(&stack);
                return 0; // Brackets do not match
            }
        }
    }
    // Step 4: after the loop, return 1 if the stack is empty (valid), otherwise 0 (extra left bracket)
    if(stackIsEmpty(&stack)) {
        stackDestroy(&stack);
        return 1;
    } else {
        stackDestroy(&stack);
        return 0;
    }
}

// Advanced stack version
// Student task: learn state management; brackets inside strings must not take part in matching, and escape characters must be handled
int jsonBracketCheckAdvanced(const char *json_str) {
// Student implementation:
// Step 1: handle edge cases (json_str is NULL or an empty string: return 1)
    if(json_str == NULL || strlen(json_str) == 0) {
        return 1; // An empty string counts as valid
    }
// Step 2: initialize the stack (call stackInit)
    Stack stack;
    if(stackInit(&stack, 10, 100) != STACK_OK) {
        return 0; // Initialization failed, treat as invalid
    }
// Step 3: initialize the state flags (in_string marks the string state, escape marks the escape state)
    int in_string = 0;
    int escape = 0;
// Step 4: walk through each character of json_str:
//        - Inside a string (in_string == 1):
//             * In escape state (escape == 1): clear the escape state and continue
//             * On the escape character '\\': enter escape state
//             * On a quote '"' outside escape state: leave the string state
//             * All brackets inside the string are ignored
//        - Outside a string (in_string == 0):
//             * On a quote '"': enter the string state
//             * Left bracket ({ / [): push (stackPush)
//             * Right bracket (} / ]): pop and check the match (isBracketMatch); return 0 on a mismatch
//             * Other characters (letters, digits, colons, etc.): skip
    for(int i = 0; json_str[i] != '\0'; i++) {
        char ch = json_str[i];
        if(in_string) {
            if(escape) {
                escape = 0; // Clear the escape state
            } else if(ch == '\\') {
                escape = 1; // Enter escape state
            } else if(ch == '"') {
                in_string = 0; // Leave the string state
            }
            // Brackets inside the string are ignored
        } else {
            if(ch == '"') {
                in_string = 1; // Enter the string state
            } else if(isLeftBracket(ch)) {
                if(stackPush(&stack, ch, i) != STACK_OK) {
                    stackDestroy(&stack);
                    return 0; // Push failed, treat as invalid
                }
            } else if(isRightBracket(ch)) {
                StackElem topElem;
                if(stackPop(&stack, &topElem) != STACK_OK) {
                    stackDestroy(&stack);
                    return 0; // Pop failed: extra right bracket
                }
                if(!isBracketMatch(topElem.bracket, ch)) {
                    stackDestroy(&stack);
                    return 0; // Brackets do not match
                }
            }
        }
    }       
// Step 5: after the loop, check that the stack is empty and we are not inside a string; return 1 if both hold, otherwise 0
    int result = (stackIsEmpty(&stack) && !in_string) ? 1 : 0;
    stackDestroy(&stack);
    return result;
}

int main(){
    char str[100];
    // Read the JSON string
    scanf("%s", str); 
    // Basic stack version
    int result1 = jsonBracketCheckBasic(str);
    // Advanced stack version
    int result2 = jsonBracketCheckAdvanced(str);
    // Print the bracket matching result; the basic version only handles simple cases, the advanced version is always correct
    printf("%d %d", result1,result2);
}