#include <asn_internal.h>
#include <asn_decode_error.h>

static __thread asn_decode_error_info_t asn_g_decode_error;

void
asn_clear_decode_error(void) {
    memset(&asn_g_decode_error, 0, sizeof(asn_g_decode_error));
    asn_g_decode_error.element_index = -1;
}

void
asn_set_decode_error(const char *type_name, const char *field_name,
                     long element_index, size_t bit_offset, int code,
                     const char *src_file, int src_line) {
    if(asn_g_decode_error.has_error) {
        /* A deeper, more specific failure was already recorded. Keep it. */
        return;
    }
    asn_g_decode_error.has_error = 1;
    asn_g_decode_error.type_name = type_name;
    asn_g_decode_error.field_name = field_name;
    asn_g_decode_error.element_index = element_index;
    asn_g_decode_error.bit_offset = bit_offset;
    asn_g_decode_error.code = code;
    asn_g_decode_error.src_file = src_file;
    asn_g_decode_error.src_line = src_line;
}

const asn_decode_error_info_t *
asn_get_last_decode_error(void) {
    return asn_g_decode_error.has_error ? &asn_g_decode_error : 0;
}
