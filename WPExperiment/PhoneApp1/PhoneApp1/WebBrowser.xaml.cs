using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;

namespace PhoneApp1
{
    public partial class WebBrowser : PhoneApplicationPage
    {
        public WebBrowser()
        {
            InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            webBrowser.Navigate(new Uri("./JavaScriptWindowScroll.html",UriKind.Relative));
        }
    }
}