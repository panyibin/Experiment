using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Phone.UI.Input;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.Web.Http;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkID=390556

namespace App8._1
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class PivotPage : Page
    {
        private double pointerDownX;
        private double pointerUpX;
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
            Browser1.Navigate(new Uri("https://www.baidu.com"));
            Browser2.Navigate(new Uri("https://www.bing.com/rewards/dashboard"));
            Browser3.Navigate(new Uri("ms-appx-web:///JavaScriptWindowScroll.html"));
            Browser4.Navigate(new Uri("https://www.bing.com/rewards/levels"));

            HardwareButtons.BackPressed += HardwareButtons_BackPressed;
        }

        private void HardwareButtons_BackPressed(object sender, BackPressedEventArgs e)
        {
            if(this.Frame != null && this.Frame.CanGoBack)
            {
                this.Frame.GoBack();

                e.Handled = true;
            }
        }

        private void Browser1_ScriptNotify(object sender, NotifyEventArgs e)
        {
            Debug.WriteLine("baidu:" + e.Value.ToString());
        }

        
        private void Browser2_ScriptNotify(object sender, NotifyEventArgs e)
        {
            WebView wb = sender as WebView;

            Debug.WriteLine("bing:" + e.Value.ToString());

            string[] field = e.Value.ToString().Split(',');

            if(field[0] == "PointerDown")
            {
                try
                {
                    if (field[1] != null)
                    {
                        pointerDownX = double.Parse(field[1]);
                    }
                }
                catch(Exception ex)
                {
                    Debug.WriteLine(ex.ToString());
                }
                
            }
            else if (field[0] == "PointerUp")
            {
                try
                {
                    if (field.Length >= 2 && field[1] != null)
                    {
                        pointerUpX = double.Parse(field[1]);
                    }
                }
                catch (Exception ex)
                {
                    Debug.WriteLine(ex.ToString());

                    return;
                }

                if(pointerUpX - pointerDownX > 20)
                {
                    if (PivotParent.SelectedIndex > 0)
                    {
                        wb.Stop(); //we call this to prevent the page from being navigated to other pages

                        PivotParent.SelectedIndex--;
                    }
                        
                }
                else if(pointerUpX - pointerDownX < -20)
                {
                    wb.Stop();

                    PivotParent.SelectedIndex++;
                }

            }
        }

        private void Browser3_ScriptNotify(object sender, NotifyEventArgs e)
        {
            Debug.WriteLine("own:" + e.Value.ToString());
        }

        private void Browser4_ScriptNotify(object sender, NotifyEventArgs e)
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
            await Browser1.InvokeScriptAsync("eval", new string[] { "document.documentElement.style.msTouchAction = 'none';window.addEventListener('pointerdown', function paint(event) {window.external.notify('PointerDown' + ',' + event.clientX + ',' + event.clientY); }, false);window.addEventListener('pointerup', function paint(event) {window.external.notify('PointerUp' + ',' + event.clientX + ',' + event.clientY); }, false);window.addEventListener('mspointerout', function paint(event) {window.external.notify('PointerOut' + ',' + event.clientX + ',' + event.clientY); }, false);" });
        }

        private async void Browser2_LoadCompleted(object sender, NavigationEventArgs e)
        {
            //await Browser2.InvokeScriptAsync("eval", new string[] {"window.onscroll = function (){window.external.notify(window.pageXOffset + ';' + document.documentElement.scrollTop + ';' + document.body.scrollTop);}"});
            //await Browser2.InvokeScriptAsync("eval", new string[] { "document.documentElement.style.msTouchAction = 'pan-y';window.addEventListener('pointerdown', function paint(event) {window.external.notify('PointerDown' + ',' + event.clientX + ',' + event.clientY); }, false);window.addEventListener('pointerup', function paint(event) {window.external.notify('PointerUp' + ',' + event.clientX + ',' + event.clientY); }, false);" });
        }

        private async void Browser3_LoadCompleted(object sender, NavigationEventArgs e)
        {
            await Browser3.InvokeScriptAsync("eval", new string[] { "window.addEventListener('pointerdown', function paint(event) {window.external.notify('PointerDown' + ',' + event.clientX + ',' + event.clientY); }, false);window.addEventListener('pointerup', function paint(event) {window.external.notify('PointerUp' + ',' + event.clientX + ',' + event.clientY); }, false);" });
        }
        private void Browser4_LoadCompleted(object sender, NavigationEventArgs e)
        {

        }

        private void Pivot_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //Pivot pt = sender as Pivot;

            //PivotItem seletedPt = pt.SelectedItem as PivotItem;

            //seletedPt.Foreground =  
        }

        private void homeButton_Click(object sender, RoutedEventArgs e)
        {
            //Browser2.Navigate(new Uri("https://www.bing.com/rewards/dashboard"));
            Frame.Navigate(typeof(MainPage));
        }

        private void refreshButton_Click(object sender, RoutedEventArgs e)
        {
            Browser2.Refresh();
            Browser4.Refresh();
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            if(Browser2.CanGoBack)
            {
                Browser2.GoBack();
            }
        }

        private void settingButton_Click(object sender, RoutedEventArgs e)
        {
            Windows.Web.Http.Filters.HttpBaseProtocolFilter myFilter = new Windows.Web.Http.Filters.HttpBaseProtocolFilter();
            var cookieManager = myFilter.CookieManager;

            HttpCookieCollection myCookieJar = cookieManager.GetCookies(new Uri("https://www.bing.com/rewards"));

            foreach(HttpCookie cookie in myCookieJar)
            {
                cookieManager.DeleteCookie(cookie);
            }
        }

        private async void Browser2_NavigationCompleted(WebView sender, WebViewNavigationCompletedEventArgs args)
        {
            try
            {
                await Browser2.InvokeScriptAsync("eval", new string[] { "document.documentElement.style.msTouchAction = 'pan-y';window.addEventListener('pointerdown', function paint(event) {window.external.notify('PointerDown' + ',' + event.clientX + ',' + event.clientY); }, false);window.addEventListener('pointerup', function paint(event) {window.external.notify('PointerUp' + ',' + event.clientX + ',' + event.clientY); }, false);window.addEventListener('mspointerout', function paint(event) {window.external.notify('PointerOut' + ',' + event.clientX + ',' + event.clientY); }, false);window.addEventListener('pointermove', function paint(event) {window.external.notify('PointerMove' + ',' + event.clientX + ',' + event.clientY); }, false);" });
            }
            catch(Exception e)
            {
                Debug.WriteLine(e.ToString());
            }
        }

        private void Browser2_NavigationFailed(object sender, WebViewNavigationFailedEventArgs e)
        {

        }

        private void navigateButton_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage));
        }
    }
}
