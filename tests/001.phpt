--TEST--
Check if say is loaded
--SKIPIF--
<?php
if (!extension_loaded('say')) {
	echo 'skip';
}
?>
--FILE--
<?php 
echo 'The extension "say" is available';
?>
--EXPECT--
The extension "say" is available
