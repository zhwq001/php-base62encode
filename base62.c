/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_base62.h"

/* If you declare any globals in php_base62.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(base62)
*/

/* True global resources - no need for thread safety here */
static int le_base62;

/* {{{ base62_functions[]
 *
 * Every user visible function must have an entry in base62_functions[].
 */
const zend_function_entry base62_functions[] = {
	PHP_FE(base62encode, NULL)
	PHP_FE(base62decode, NULL)
	{ NULL, NULL, NULL, 0, 0 }/* Must be the last line in base62_functions[] */
};
/* }}} */

/* {{{ base62_module_entry
 */
zend_module_entry base62_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"base62",
	base62_functions,
	NULL,
	NULL,
	NULL,		/* Replace with NULL if there's nothing to do at request start */
	NULL,	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(base62),
#if ZEND_MODULE_API_NO >= 20010901
	"0.2", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BASE62
ZEND_GET_MODULE(base62)
#endif


/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(base62)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "base62 support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

#define BASE62_LEN 62
#define BASE62_STRING "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

static char* unshift_char (char* str, const char c)
{/*{{{*/
	char buf[12], *rst=str;
	int idx=0;
	strcpy(buf, str);
	*str++ = c;
	while((*str++ = buf[idx++]) != '\0');
	return rst;
}/*}}}*/

static char* do_base62_encode( long long rawInt)
{/*{{{*/
	char buff[12], *rst;
	long long be = rawInt;
	buff[0] = '\0';
	while(be>0) {
		unshift_char(buff, BASE62_STRING[be%BASE62_LEN]);
		be = floor(be/BASE62_LEN);
	}
	int buff_l = strlen(buff);
	rst = (char*) safe_emalloc(buff_l, sizeof(char), 1);
	strncpy(rst, buff, buff_l);
	*(rst+buff_l) = '\0';
	return rst;
}/*}}}*/

static long long do_base62_decode(const char* raw)
{/*{{{*/
	long long rst=0, base=1;
	char* pos;
	const char* end=raw+strlen(raw)-1;
	while(end != (raw-1))
	{
		rst = rst+base*(strchr(BASE62_STRING, *end--)-BASE62_STRING);
		base *= BASE62_LEN;
	}
	return rst;
	
}/*}}}*/

static int validate_encode_str(char* str)
{/*{{{*/
	int rst = 1;
	char c;
	while((c=*str++)!='\0') {
		if (c<48 || (c>57 && c<65) || (c>90 && c<97)|| c>122) {
			rst=0;
			break;
		}
	}
	return rst;
}/*}}}*/

PHP_FUNCTION(base62encode)
{/*{{{*/
	long long rawInt;
	char *rst;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &rawInt)==FAILURE) {
		return;
	}
	if (rawInt < 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Argument has to be greater than or equal to 0");
		RETURN_NULL();
	}
	rst = do_base62_encode(rawInt);
	RETURN_STRING(rst, 0);
}/*}}}*/

PHP_FUNCTION(base62decode)
{/*{{{*/
	char* raw;
	int raw_l;
	long long rtn;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &raw, &raw_l)==FAILURE) {
		return;
	}
	if (strlen(raw)>11 || !validate_encode_str(raw))
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "invalid argument!");
		RETURN_LONG(0);
	}
	rtn = do_base62_decode(raw);
	RETURN_LONG(rtn);
}/*}}}*/

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
