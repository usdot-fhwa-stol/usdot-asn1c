TESTS_ENVIRONMENT= MAKE=${MAKE}                     \
                    top_builddir=${top_builddir}    \
                    top_srcdir=${top_srcdir}

TESTS =
TESTS += check-INTEGER.sh
TESTS += check-INTEGER_0_1.sh
TESTS += check-ENUMERATED_foo.sh
TESTS += check-NULL.sh
TESTS += check-BOOLEAN.sh
TESTS += check-BIT_STRING.sh
TESTS += check-OBJECT_IDENTIFIER.sh
TESTS += check-RELATIVE-OID.sh
TESTS += check-SEQUENCE_f_INTEGER.sh
TESTS += check-CHOICE_f_INTEGER.sh
TESTS += check-OCTET_STRING.sh
TESTS += check-IA5String.sh
TESTS += check-IA5String_SIZE_1.sh
TESTS += check-UTF8String.sh
TESTS += check-REAL.sh
TESTS += check-SET_OF_INTEGER.sh
TESTS += check-SEQUENCE_OF_INTEGER.sh

CLEANFILES = Makefile.am.* *.[acho] check-*.log check-*.trs

EXTRA_DIST = README $(srcdir)/check-*.sh

clean-local:
	rm -rf test-*

