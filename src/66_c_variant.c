
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// -----------------------------------------------------------------------------
// USER INSTRUCTIONS:
// 1. Read 'src/66_c_variant.md' for memory layout and trap analysis.
// 2. Implement the missing TODO blocks using strict type discipline.
// 3. Observe how raw C access differs from C++ std::variant safety.
// -----------------------------------------------------------------------------

// 01. Define Tag Enum
typedef enum { 
    TAG_INT = 0, 
    TAG_FLOAT = 1,
    TAG_ERROR = 0xFF // Guard against uninitialized 0 if we want
} VariantTag;

// 02. Define Variant Struct
typedef struct {
    VariantTag tag;          // 4 bytes (usually)
    union {
        int32_t i;           // 4 bytes
        float f;             // 4 bytes
    } data;
} Variant;                   // Total 8 bytes aligned

// 03. Safe Setter: Integer
// TODO: Implement sequence: Set Data FIRST, then Tag.
// Why: Avoid race condition where ISR sees Tag=INT but Data=OldFloat.
void variant_set_int(Variant *v, int32_t value) {
    // 1. Set data first
    v->data.i = value;
    // 2. Memory barrier (conceptually check with __sync_synchronize() if needing actual atomic)
    // 3. Set tag last
    v->tag = TAG_INT;
}

// 04. Safe Setter: Float
void variant_set_float(Variant *v, float value) {
    v->data.f = value;
    v->tag = TAG_FLOAT;
}

// 05. Safe Getter: Integer
// Returns true if type matches, writes to out.
// Returns false if mismatch.
bool variant_get_int(const Variant *v, int32_t *out) {
    if (v->tag == TAG_INT) {
        *out = v->data.i;
        return true;
    }
    return false;
}

// 06. Safe Getter: Float
bool variant_get_float(const Variant *v, float *out) {
    if (v->tag == TAG_FLOAT) {
        *out = v->data.f;
        return true;
    }
    return false;
}

// 07. Debug Printer (The "Visitor")
void variant_print(const Variant *v) {
    switch (v->tag) {
        case TAG_INT:
            printf("INT: %d\n", v->data.i);
            break;
        case TAG_FLOAT:
            printf("FLOAT: %f\n", (double)v->data.f);
            break;
        case TAG_ERROR:
            printf("ERROR: Uninitialized/Error State\n");
            break;
        default:
            printf("UNKNOWN TAG: %x\n", (unsigned int)v->tag);
            break;
    }
}

int main() {
    printf("--- 01. Initialization & Safety ---\n");
    
    // Exercise 1: Uninitialized Variable
    Variant garbage;
    (void)garbage; // Silence warning if not printing
    // variant_print(&garbage); // Danger!

    // Exercise 2: Correct Init
    Variant v = { .tag = TAG_ERROR }; // Explicit safe state
    
    printf("--- 02. Set & Get Integer ---\n");
    // TODO: Set to 42 using helper
    variant_set_int(&v, 42);
    
    int32_t val_i;
    // TODO: Get int successfully
    if (variant_get_int(&v, &val_i)) printf("Got Int: %d\n", val_i);
    
    // TODO: Try to get float (should fail)
    float val_f;
    if (!variant_get_float(&v, &val_f)) printf("Float access denied (Correct)\n");

    printf("--- 03. Type Switching ---\n");
    // TODO: Switch to float 3.14
    variant_set_float(&v, 3.14f);
    
    // TODO: Print using visitor
    variant_print(&v);
    
    printf("--- 04. Raw Memory Inspection ---\n");
    // TODO: Print the hex bytes of the variant to see Tag vs Data
    uint8_t *bytes = (uint8_t*)&v;
    printf("Memory: ");
    for(size_t i=0; i<sizeof(Variant); i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
    // Identify: Which bytes are tag? Which are float? (Assume Little Endian)
    
    return 0;
}
