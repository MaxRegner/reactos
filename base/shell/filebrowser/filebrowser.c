* License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <shobjidl.h>
#include <shlobj.h>
#include <shlwapi.h>

#include <browseui_undoc.h>

int _tmain(int argc, _TCHAR* argv[])
{
    EXPLORER_CMDLINE_PARSE_RESULTS parseResults = { 0 };

    if (SHExplorerParseCmdLine(&parseResults))

    {
        IShellBrowser *psb;
        IShellView *psv;
        IShellFolder *psf;
        LPITEMIDLIST pidl;
        HRESULT hr;

        hr = SHExplorerCreateShellBrowser(&psb);
        if (SUCCEEDED(hr))
        {
            hr = SHExplorerCreateShellView(&parseResults, psb, &psv);
            if (SUCCEEDED(hr))
            {
                hr = IShellView_QueryInterface(psv, &IID_IShellFolder, (void**)&psf);
                if (SUCCEEDED(hr))
                {
                    hr = IShellFolder_ParseDisplayName(psf, NULL, NULL, parseResults.szPath, NULL, &pidl, NULL);
                    if (SUCCEEDED(hr))
                    {
                        hr = IShellView_Initialize(psv, psf, pidl);
                        if (SUCCEEDED(hr))
                        {
                            hr = IShellBrowser_BrowseObject(psb, pidl, SBSP_ABSOLUTE);
                            if (SUCCEEDED(hr))
                            {
                                MSG msg;
                                while (GetMessage(&msg, NULL, 0, 0))
                                {
                                    TranslateMessage(&msg);
                                    DispatchMessage(&msg);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    {
        parseResults.dwFlags |= SH_EXPLORER_CMDLINE_FLAG_SEPARATE;
        parseResults.nCmdShow = SW_SHOWNORMAL;
        return SHCreateFromDesktop(&parseResults);
    }

    return 1;
}

    if (parseResults.strPath)
        SHFree(parseResults.strPath);

    if (parseResults.pidlPath)
        ILFree(parseResults.pidlPath);

    if (parseResults.pidlRoot)
        ILFree(parseResults.pidlRoot);

    return 0;
}
