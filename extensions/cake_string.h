#ifndef CAKE_STRING_H_ 
#define CAKE_STRING_H_ 

typedef struct {
    size_t size;
    size_t capacity;
    char *es;
} Cake_String;

void cake_string_print(Cake_String cs); 

Cake_String cake_string_from_cstr(char* cstr); 
void cake_string_trim_right(Cake_String *cs); 

#ifdef CAKE_STRING_IMPLEMENTATION 

void cake_string_print(Cake_String cs)
{
    for (size_t i=0; i<cs.size; ++i) {
        printf("%c", cs.es[i]);
    }
    printf("\n");
}

Cake_String cake_string_from_cstr(char* cstr)
{
    Cake_String cs = {0};
    // TODO: what about the temporary allocator ?? 
    cs.es = cake_talloc_poll(sizeof(cstr));
    for (size_t i=0; i<strlen(cstr); ++i) {
        cs.es[i] = cstr[i];
    }
    cs.size = strlen(cstr);
    return cs;
}

void cake_string_trim_right(Cake_String *cs)
{
    size_t new_size = cs->size;
    while (new_size > 0 && (cs->es[new_size-1] == ' ' || cs->es[new_size-1] == '\n')) {
        new_size -= 1;
    }
    cs->size = new_size;
}

#endif // CAKE_STRING_IMPLEMENTATION 
#endif // CAKE_STRING_H_ 
