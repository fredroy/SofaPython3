/******************************************************************************
*                              SofaPython3 plugin                             *
*                  (c) 2021 CNRS, University of Lille, INRIA                  *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/

#include "Binding_Utils.h"

#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <sofa/helper/Utils.h>

namespace py { using namespace pybind11; }

namespace sofapython3
{

void moduleAddUtils(py::module& m)
{
    py::class_<sofa::helper::Utils> utils(m, "Utils");

    /*
     * Sofa.Helper.Utils.GetSofaUserLocalDirectory
     */
    const auto getSofaUserLocalDirectoryDoc = R"doc(
        Return the configuration folder for the current user (and OS).

        :return: A string with the path to the configuration folder.
    )doc";

    utils.def_static("GetSofaUserLocalDirectory", py::overload_cast<>(&sofa::helper::Utils::getSofaUserLocalDirectory), getSofaUserLocalDirectoryDoc);
}

} /// namespace sofapython3
