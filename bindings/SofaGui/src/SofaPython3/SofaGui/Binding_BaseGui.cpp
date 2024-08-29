/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2021 INRIA, USTL, UJF, CNRS, MGH                     *
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

#include "Binding_BaseGui.h"

#include <sofa/gui/common/BaseGUI.h>
#include <sofa/simulation/Node.h>

namespace py = pybind11;

namespace sofapython3 {
using sofa::gui::common::BaseGUI;
using sofa::simulation::Node;

void moduleAddBaseGui(py::module& m)
{
    py::class_<sofa::gui::common::BaseGUI, std::unique_ptr<sofa::gui::common::BaseGUI, py::nodelete>> baseGUI(m, "BaseGUI");

    /*
     * Sofa.Gui.BaseGUI.SetBackgroundImage
     */
    const auto SetBackgroundImageDoc = R"doc(
        Set the background image of the current GUI viewer with the given filepath.

        :param filename: Path to the image which will become the background of the viewer.
        :type filename: str
    )doc";
    baseGUI.def("setBackgroundImage", &sofa::gui::common::BaseGUI::setBackgroundImage, SetBackgroundImageDoc);

    /*
     * Sofa.Gui.BaseGUI.SetConfigDirectoryPath
     */
    const auto SetConfigDirectoryPathDoc = R"doc(
        Set the configuration directory.

        :param filename: Path the configuration directory to set.
        :type filename: str
    )doc";
    baseGUI.def_static("SetConfigDirectoryPath", &sofa::gui::common::BaseGUI::setConfigDirectoryPath, SetConfigDirectoryPathDoc);

    /*
     * Sofa.Gui.BaseGUI.closeGUI
     */
    const auto closeGUIDoc = R"doc(
        Close the current GUI.
    )doc";
    baseGUI.def("closeGUI", &sofa::gui::common::BaseGUI::closeGUI, closeGUIDoc);


    /*
     * Sofa.Gui.BaseGUI.MainLoop
     */
    const auto mainLoopDoc = R"doc(
        Main loop of the GUI.

        Calling the main loop will steal the execution control of the script until the GUI is closed.

        :param node: The root node of the current scene to draw into the GUI.
        :type node: Node&
        :param filename: The current script filename (optional)
        :type filename: str
        :return: 0 if the main loop succeed, 1 otherwise
    )doc";
    baseGUI.def("mainLoop", &sofa::gui::common::BaseGUI::mainLoop, mainLoopDoc);


    /*
     * Sofa.Gui.BaseGUI.SetDimension
     */
    const auto setDimensionDoc = R"doc(
        Set the GUI's dimensions.

        This must be called after Sofa.Gui.BaseGUI.createGUI

        :param width:
        :type width: int
        :param height:
        :type height: int
    )doc";
    baseGUI.def("setDimension", &sofa::gui::common::BaseGUI::setViewerResolution, setDimensionDoc);

    /*
     * Sofa.Gui.BaseGUI.CenterWindow
     */
    const auto centerWindowDoc = R"doc(
        Center the GUI's window on screen .

        This must be called after Sofa.Gui.BaseGUI.createGUI

    )doc";
    baseGUI.def("centerWindow", &sofa::gui::common::BaseGUI::centerWindow, centerWindowDoc);

    /*
     * Sofa.Gui.BaseGUI.SetFullScreen
     */
    const auto SetFullScreenDoc = R"doc(
        Set the GUI in full screen mode.
    )doc";
    baseGUI.def("setFullScreen", &sofa::gui::common::BaseGUI::setFullScreen, SetFullScreenDoc);

    /*
     * Sofa.Gui.BaseGUI.SaveScreenshot
     */
    const auto SaveScreenshotDoc = R"doc(
        Save the current frame into a file.

        :param filename: Where to save the screenshot.
        :type filename: str
    )doc";
    baseGUI.def("saveScreenshot", &sofa::gui::common::BaseGUI::saveScreenshot, SaveScreenshotDoc);

    /*
     * Sofa.Gui.GUIManager.SetScene
     */
    const auto setSceneDoc = R"doc(
        Set the active scene.

        :param node: The root node of the current scene to draw into the GUI.
        :type node: Node&
        :param filename: The current script filename (optional)
        :type filename: str
        :param temporaryFile: Whether the file is temporary (default to false)
        :type temporaryFile: bool
    )doc";
    baseGUI.def("setScene", [](sofa::gui::common::BaseGUI& self, sofa::simulation::Node& node, const char* filename = nullptr, bool temporaryFile = false) {
        self.setScene(&node, filename, temporaryFile);
        }, py::arg("root"), py::arg("filename") = nullptr, py::arg("temporaryFile") = false, setSceneDoc);

}

} // namespace sofapython3
