#include "magic_square_threaded.h"

magic_solver *set_magic_solver(int array, int line_sum, int diag_1, int diag_2, int target, int i, int j)
{
    magic_solver *ms = malloc(sizeof(magic_solver));
    ms->array = array;
    ms->line_sum = line_sum;
    ms->diag_1 = diag_1;
    ms->diag_2 = diag_2;
    ms->target = target;
    ms->i = i;
    ms->j = j;
    return ms;
}