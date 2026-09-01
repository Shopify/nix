#pragma once
///@file

#include "nix/expr/eval.hh"

#include <tuple>
#include <vector>

namespace nix {

struct RegisterPrimOp
{
    typedef std::vector<PrimOp> PrimOps;

    static PrimOps & primOps();

    /**
     * You can register a constant by passing an arity of 0. fun
     * will get called during EvalState initialization, so there
     * may be primops not yet added and builtins is not yet sorted.
     */
    RegisterPrimOp(PrimOp && primOp);
};

/* These primops are disabled without enableNativeCode, but plugins
   may wish to use them in limited contexts without globally enabling
   them. */

/**
 * Load a ValueInitializer from a DSO and return whatever it initializes
 */
void prim_importNative(EvalState & state, const PosIdx pos, Value ** args, Value & v);

/**
 * Execute a program and parse its output
 */
void prim_exec(EvalState & state, const PosIdx pos, Value ** args, Value & v);

/**
 * Convert a store derivation (a `.drv` store path) into a derivation-shaped
 * attrset value (`type`, `name`, `drvPath`, `outPath`, `outputs`, per-output
 * attrs), as importing a `.drv` file does. `path` is the source path whose
 * string form becomes the value's `drvPath`; `storePath` must name a valid
 * store derivation.
 */
void derivationToValue(
    EvalState & state, const PosIdx pos, const SourcePath & path, const StorePath & storePath, Value & v);

void makePositionThunks(EvalState & state, const PosIdx pos, Value & line, Value & column);

} // namespace nix
