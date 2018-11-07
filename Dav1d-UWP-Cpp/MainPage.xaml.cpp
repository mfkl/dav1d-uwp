//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "dav1d/dav1d.h"

using namespace Dav1d_UWP_Cpp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	Loaded += ref new Windows::UI::Xaml::RoutedEventHandler(this, &Dav1d_UWP_Cpp::MainPage::OnLoaded);	
}

void Dav1d_UWP_Cpp::MainPage::OnLoaded(Object ^sender, RoutedEventArgs ^e)
{
	const char *version = dav1d_version();
	
	Dav1dSettings lib_settings;
	Dav1dContext *c;
	int res = 0;
	Dav1dData data;
	Dav1dPicture p;
	unsigned n_out = 0, total, fps[2];

	dav1d_default_settings(&lib_settings);

	if ((res = dav1d_open(&c, &lib_settings)))
		return;

	/*do {
		memset(&p, 0, sizeof(p));
		if ((res = dav1d_decode(c, &data, &p)) < 0) {
			if (res != -EAGAIN) {
				fprintf(stderr, "Error decoding frame: %s\n",
					strerror(-res));
				break;
			}
			res = 0;
		}
		else {
			if (!n_out) {
				if ((res = output_open(&out, cli_settings.muxer,
					cli_settings.outputfile,
					&p.p, fps)) < 0)
				{
					return res;
				}
			}
			if ((res = output_write(out, &p)) < 0)
				break;
			n_out++;
			if (!cli_settings.quiet)
				print_stats(istty, n_out, total);
		}

		if (cli_settings.limit && n_out == cli_settings.limit)
			break;
	} while (data.sz > 0 || !input_read(in, &data));*/

}
