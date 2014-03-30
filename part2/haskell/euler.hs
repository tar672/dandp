import Control.Parallel.Strategies

hcf x 0 = x
hcf x y = hcf y (rem x y)

relprime x y = hcf x y == 1

euler m = length (filter (relprime m) [1 .. m-1])

sumTotient lower upper = sum ((map euler [lower .. upper]) `using` parAscListChunk 50 rseq)

main = print (sumTotient 1 30000)



parAscListRevPair n strat xs = 
	parListChunk n strat (reorder xs)

reorder xs = merge (take (ll xs) xs) (reverse (drop (ll xs) xs))

ll xs = (length xs) `quot` 2

merge xs     []     = xs
merge []     ys     = ys
merge (x:xs) (y:ys) = x : y : merge xs ys




