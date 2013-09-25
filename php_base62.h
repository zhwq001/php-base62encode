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

#ifndef PHP_BASE62_H
#define PHP_BASE62_H

extern zend_module_entry base62_module_entry;
#define phpext_base62_ptr &base62_module_entry

#ifdef PHP_WIN32
#	define PHP_BASE62_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_BASE62_API __attribute__ ((visibility("default")))
#else
#	define PHP_BASE62_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINFO_FUNCTION(base62);

PHP_FUNCTION(base62encode);
PHP_FUNCTION(base62decode);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(base62)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(base62)
*/

/* In every utility function you add that needs to use variables 
   in php_base62_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as BASE62_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define BASE62_G(v) TSRMG(base62_globals_id, zend_base62_globals *, v)
#else
#define BASE62_G(v) (base62_globals.v)
#endif

#endif	/* PHP_BASE62_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
