import Data.List
import Data.Function
import System.Environment

type Point = (Int, Int, Int)

readLine :: String -> Point
readLine s = 
    let (a:b:c:_) = map read $ words s
    in (a,b,c)

parse :: String -> [Point]
parse xs = map readLine $ lines xs

showLine :: Point -> String
showLine (a,b,c) = unwords $ map show [a,b,c]

unparse :: [Point] -> String
unparse xs = unlines $ map showLine xs

distance :: Point -> Point -> Int
distance (_,x1,y1) (_,x2,y2) = 
    let dx = x1 - x2
        dy = y1 - y2
    in dx^2 + dy^2

solve :: [Point] -> [Point]
solve [] = []
solve (x:xs) =
    let sorted = sortBy (compare `on` (distance x)) xs
    in [x] ++ solve sorted

cycle' :: Int -> [Point] -> [Point]
cycle' 0 xs = xs
cycle' i (x:xs) = cycle' (i - 1) xs ++ [x]

main = do
    args <- getArgs  
    let i = read . head $ args 
    n <- getLine
    testcase <- getContents
    putStr $ unwords (map (\(id,_,_) -> (show id)) (solve . (cycle' i) . parse $ testcase ))