import Control.Parallel.Strategies

hcf x 0 = x
hcf x y = hcf y (rem x y)

relprime x y = hcf x y == 1

eulersum m = length (filter (relprime m) [1 .. m-1])

euler xs = sum (map eulersum xs)

split xs = split' 2 (reverse xs)
split' m [] = []
split' m xs = ( take (getl m) xs ):( split' (m + 1) (drop (getl m) xs) )

getl l = abs(floor(logBase 1.1 l))


sumTotient lower upper = sum (parMap rpar euler (split [lower .. upper]))


main = print (sumTotient 1 100000)
