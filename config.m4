PHP_ARG_ENABLE(say, whether to enable say support,
[  --enable-say          Enable say support], no)

if test "$PHP_SAY" != "no"; then
  AC_DEFINE(HAVE_SAY, 1, [ Have say support ])
  PHP_NEW_EXTENSION(say, say.c, $ext_shared)
fi
