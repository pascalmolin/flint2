/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_mat.h"
#include "nmod_mat.h"
#include "ulong_extras.h"
#include "long_extras.h"

int
main(void)
{
    int i;
    flint_rand_t state;
    flint_randinit(state);

    printf("scalar_mod_fmpz....");
    fflush(stdout);

    for (i = 0; i < 10000; i++)
    {
        fmpz_mat_t A, Amod;
        fmpz_t mod;

        long rows, cols;

        rows = n_randint(state, 20);
        cols = n_randint(state, 20);

        fmpz_mat_init(A, rows, cols);
        fmpz_mat_init(Amod, rows, cols);
        fmpz_init(mod);

        fmpz_randtest_not_zero(mod, state, 100);

        fmpz_mat_randtest(A, state, 100);
        fmpz_mat_randtest(Amod, state, 100);

        fmpz_mat_scalar_mod_fmpz(Amod, A, mod);
        fmpz_mat_scalar_mod_fmpz(A, A, mod);

        if (!fmpz_mat_equal(A, Amod))
        {
            printf("FAIL: aliasing!\n");
            abort();
        }

        fmpz_mat_clear(A);
        fmpz_mat_clear(Amod);
        fmpz_clear(mod);
    }

    flint_randclear(state);

    _fmpz_cleanup();
    printf("PASS\n");
    return 0;
}