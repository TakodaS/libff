/** @file
 *****************************************************************************
 * @author     This file is part of libff, developed by SCIPR Lab
 *             and contributors (see AUTHORS).
 * @copyright  MIT license (see LICENSE file)
 *****************************************************************************/

#ifndef BN_UTILS_HPP_
#define BN_UTILS_HPP_
#include <vector>
#include <cstdint>

namespace mie
{
    class Fp;
    namespace local
    {
        template <typename T, std::size_t S>
        class FixedBuffer;
    }

    template <typename T>
    class VuintT;

    typedef VuintT<local::FixedBuffer<uint64_t, 576>> Vuint;

}
namespace bn
{
    typedef mie::Fp Fp;
    template <class T>
    class Fp2T;
    typedef Fp2T<Fp> Fp2;
    template <class T>
    class Fp6T;
    typedef Fp6T<Fp2> Fp6;
    template <class T>
    class Fp12T;
    typedef Fp12T<Fp6> Fp12;
}
namespace libff
{

    template <typename FieldT>
    void bn_batch_invert(std::vector<FieldT> &vec);

} // namespace libff

#endif // BN_UTILS_HPP_
