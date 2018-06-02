--TEST--
say_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('say')) {
	echo 'skip';
}
?>
--FILE--
<?php 
$ret = say_test1();

var_dump($ret);
?>
--EXPECT--
The extension say is loaded and working!
NULL
