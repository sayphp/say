/* say extension for PHP */

#ifndef PHP_SAY_H
# define PHP_SAY_H

PHP_FUNCTION(get);
PHP_FUNCTION(req);
PHP_FUNCTION(prt);

extern zend_module_entry say_module_entry;
# define phpext_say_ptr &say_module_entry

# define PHP_SAY_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_SAY)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_SAY_H */
