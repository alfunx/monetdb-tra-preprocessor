select * from tra ((select a, b, d as id from x_test) as t on a, b order by id);
