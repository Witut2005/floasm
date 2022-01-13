
;BEGIN

$ax = $cx
$dx += $bx
$sp -= $bp

$si++
$di--
$ax++

br00h_moment:

jmp br00h_moment

END
