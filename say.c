/* 
 * say extension for PHP 
 * Authors: Say <whoam163@163.com>
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_say.h"

/* {{{ void say_test1()
 */
PHP_FUNCTION(say_test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "say");
}
/* }}} */

/* {{{ string say_test2( [ string $var ] )
 */
PHP_FUNCTION(say_test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

/* proto zval get(string $key [, string default [, int $is]])
 * Returns the $_GET[$key]/$_POST[$key] as safe process
 */
PHP_FUNCTION(get)
{
	HashTable *_GET;
	HashTable *_POST;
	zval *stuff = NULL, *def = NULL;
	zend_bool is = 0;
	char *var = "";
	size_t var_len = 0;

	ZEND_PARSE_PARAMETERS_START(1, 3)
		Z_PARAM_STRING(var, var_len)
        Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(def)
        Z_PARAM_BOOL(is)
	ZEND_PARSE_PARAMETERS_END();

	_GET = Z_ARRVAL(PG(http_globals)[TRACK_VARS_GET]);
    stuff = zend_hash_str_find(_GET, var, var_len);
	if(NULL == stuff){//*GET获取失败
	    _POST = Z_ARRVAL(PG(http_globals)[TRACK_VARS_POST]);
	    stuff = zend_hash_str_find(_POST, var, var_len);
	    if(NULL == stuff){//*POST获取失败
			//*必须参数
			if(is){
                zend_throw_exception_ex(NULL, 0, "参数%s必须", var);
			}
	    	//*默认值
			if(NULL != def){
                switch(Z_TYPE_INFO_P(def)){
                    case IS_UNDEF:
                    case IS_NULL:
                        RETURN_NULL();
                        break;
                    case IS_FALSE:
    //					ZVAL_FALSE(&stuff);
                        RETURN_BOOL(0);
                        break;
                    case IS_TRUE:
    //					ZVAL_TRUE(&stuff);
                        RETURN_BOOL(1);
                        break;
                    case IS_LONG:
    //					ZVAL_LONG(&stuff, Z_LVAL_P(def));
                        RETURN_LONG(Z_LVAL_P(def));
                        break;
                    case IS_DOUBLE:
    //					ZVAL_DOUBLE(&stuff, Z_DVAL_P(def));
                        RETURN_DOUBLE(Z_DVAL_P(def));
                        break;
                    case IS_STRING:
    //					ZVAL_STR(&stuff, Z_STR_P(def));
                        RETURN_STR(Z_STR_P(def));
                        break;
                    default:
                        zend_throw_exception(NULL, "默认值数据类型错误", 0);
                }
			}
	    }
	}
    //输入参数
    if(NULL == stuff){
        RETURN_NULL();
    }
    switch(Z_TYPE_P(stuff)){
        case IS_NULL:
            RETURN_NULL();
            break;
        case IS_FALSE:
            RETURN_BOOL(0);
            break;
        case IS_TRUE:
            RETURN_BOOL(1);
            break;
        case IS_LONG:
            RETURN_LONG(Z_LVAL_P(stuff));
            break;
        case IS_DOUBLE:
            RETURN_DOUBLE(Z_DVAL_P(stuff));
            break;
        case IS_STRING:
            php_printf("is string\n");
            RETURN_STR(Z_STR_P(stuff));
            break;
        case IS_ARRAY:
            RETURN_ARR(Z_ARRVAL_P(stuff));
            break;
        default:
//                php_printf("z\n");
            zend_throw_exception_ex(NULL, 0, "参数%s:%s数据类型错误%u", var, Z_LVAL_P(stuff), Z_TYPE_INFO_P(stuff));
    }
//	php_printf("e\n");
}
/* */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(say)
{
#if defined(ZTS) && defined(COMPILE_DL_SAY)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(say)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "say support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_say_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_say_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_get, 0)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ say_functions[]
 */
static const zend_function_entry say_functions[] = {
	PHP_FE(say_test1,		arginfo_say_test1)
	PHP_FE(say_test2,		arginfo_say_test2)
	PHP_FE(get, arginfo_get)
	PHP_FE_END
};
/* }}} */

/* {{{ say_module_entry
 */
zend_module_entry say_module_entry = {
	STANDARD_MODULE_HEADER,
	"say",					/* Extension name */
	say_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(say),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(say),			/* PHP_MINFO - Module info */
	PHP_SAY_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SAY
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(say)
#endif
