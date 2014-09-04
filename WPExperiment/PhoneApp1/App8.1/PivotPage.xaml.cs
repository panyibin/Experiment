using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkID=390556

namespace App8._1
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class PivotPage : Page
    {
        public PivotPage()
        {
            this.InitializeComponent();

            //Browser1.AddHandler()
        }

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.
        /// This parameter is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            //Browser1.Navigate(new Uri("https://www.bing.com/rewards/dashboard?setmkt=en-us"));
            //Browser2.Navigate(new Uri("https://www.bing.com/rewards/levels?mobileAppId=wprwappv2"));
            Browser1.Navigate(new Uri("http://www.baidu.com"));
            Browser2.Navigate(new Uri("https://www.bing.com/rewards/dashboard"));
            Browser3.Navigate(new Uri("ms-appx-web:///JavaScriptWindowScroll.html"));
        }

        private void Browser1_ScriptNotify(object sender, NotifyEventArgs e)
        {

        }

        private void Browser2_ScriptNotify(object sender, NotifyEventArgs e)
        {

        }

        private void Browser3_ScriptNotify(object sender, NotifyEventArgs e)
        {

        }

        private async void Browser_LoadCompleted(object sender, NavigationEventArgs e)
        {
            WebView wb = sender as WebView;

            //ExecuteScript(wb);

            await wb.InvokeScriptAsync("eval", new string[] { "window.addEventListener('MSPointerMove', function paint(event) {window.external.notify(event.clientX + ',' + event.clientY); }, false);" });
        }

        async private void ExecuteScript(WebView wb)
        {
            await wb.InvokeScriptAsync("eval", new string[] { "window.onscroll = function(){ alert(\"scroll\");};" });
        }

        private async void Browser1_LoadCompleted(object sender, NavigationEventArgs e)
        {
            await Browser1.InvokeScriptAsync("eval", new string[] { "window.addEventListener('MSPointerMove', function paint(event) {window.external.notify(event.clientX + ',' + event.clientY); }, false);" });
        }

        private async void Browser2_LoadCompleted(object sender, NavigationEventArgs e)
        {
            //await Browser2.InvokeScriptAsync("eval", new string[] {"window.onscroll = function (){window.external.notify(window.pageXOffset + ';' + document.documentElement.scrollTop + ';' + document.body.scrollTop);}"});
            await Browser2.InvokeScriptAsync("eval", new string[] { "window.addEventListener('MSPointerDown', function paint(event) {window.external.notify(event.clientX + ',' + event.clientY); }, false);" });
        }

        private async void Browser3_LoadCompleted(object sender, NavigationEventArgs e)
        {
            await Browser3.InvokeScriptAsync("eval", new string[] { "window.addEventListener('MSPointerMove', function paint(event) {window.external.notify(event.clientX + ',' + event.clientY); }, false);" });
        }
    }
}
