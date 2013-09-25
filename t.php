<?php
/*$start = microtime(true);
for ($i=13284129;$i<13384129;$i++) {
    if (base62encode($i) != encode62($i)) {
        echo "{$i}\n";
    }
}
echo microtime(true)-$start,"\n";exit;
 */
$start = microtime(true);
for ($i=13284129357;$i<93284129357;$i+=100000000)
{
    $data = base62encode($i);
    $dedata = base62decode($data);
}
echo microtime(true)-$start,'---',$data. ':'. $dedata. ":{$i}", "\n";
$start = microtime(true);
for ($i=13284129357;$i<93284129357;$i+=100000000)
{
    $data = encode62($i);
    $dedata = decode62($data);
}

echo microtime(true)-$start,'---',$data. ":". $dedata. ":{$i}", "\n";

function encode62($str) {
    $out = '';
    $string = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    while($str > 0){
        $idx = $str % 62;
        $out = substr($string, $idx, 1) . $out;
        $str = floor($str / 62);
    }
    return $out;
}

function decode62($str)
{
$string='0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
$out = 0;
$base = 1;
for ( $t = strlen($str) - 1; $t >= 0; $t-=1 )
{
$out = $out + $base * strpos($string, substr($str, $t, 1));
$base *= 62;
}
return $out . "";
}
