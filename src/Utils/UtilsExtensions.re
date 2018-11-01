let flip = (f, x, y) => f(y, x);

let (<<) = (f, g, x) => f(g(x));