
;BEGIN

$ax = $cx
$dx += $bx
$sp -= $bp

$si++
$di--

dd 0x11111111

huj_piwo:
    dq 0x1123456789abcdef




END
