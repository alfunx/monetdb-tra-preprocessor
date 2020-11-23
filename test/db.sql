DROP TABLE x_test;
DROP TABLE y_test;

START TRANSACTION;

CREATE TABLE "x_test" (
    "id"                   integer NOT NULL,
    "a"                    float NOT NULL,
    "b"                    float NOT NULL,
    "c"                    integer NOT NULL,
    "d"                    varchar(255) NOT NULL
);

INSERT INTO "x_test" VALUES (0, 10201, 1, 8, 'm');
INSERT INTO "x_test" VALUES (1, 0, 3, 6, 'i');
INSERT INTO "x_test" VALUES (2, 25, 3, 3, 'j');
INSERT INTO "x_test" VALUES (3, 2.25, 1, 5, 'k');
INSERT INTO "x_test" VALUES (4, 1, 3, 6, 'l');

CREATE TABLE "y_test" (
    "id"                   integer NOT NULL,
    "e"                    integer NOT NULL,
    "f"                    integer NOT NULL,
    "g"                    integer NOT NULL,
    "h"                    integer NOT NULL
);

INSERT INTO "y_test" VALUES (0, 1, 2, 4, 3);
INSERT INTO "y_test" VALUES (0, 2, 4, 1, 2);
INSERT INTO "y_test" VALUES (1, 3, 3, 1, 9);
INSERT INTO "y_test" VALUES (2, 4, 3, 2, 8);
INSERT INTO "y_test" VALUES (2, 1, 4, 4, 9);

COMMIT;
