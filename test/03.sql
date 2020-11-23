select id, i, cast(j as int) as j, m from tra
    ((select a, b,
             cast(c as double) as c,
             cast(e as double) as e,
             cast(f as double) as f,
             cast(g as double) as g,
             cast(h as double) as h,
             d as id
        from x_test join y_test using (id)
        where e > 1) as t
    on a, b, c, e, f, g, h
    order by id);
