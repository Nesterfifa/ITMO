main = do
    x <- getLine
    y <- getLine
    let res = (read x :: Integer) * (read y :: Integer)
    print(res)