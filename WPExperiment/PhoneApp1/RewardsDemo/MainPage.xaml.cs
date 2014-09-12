using System;
using System.Collections.Generic;
using System.Diagnostics;
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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=391641

namespace RewardsDemo
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private bool isNewPageInstance = false;
        private double pointerDownX;
        private double pointerUpX;
        private bool bPointerDown = false;
        private bool bSwitchingPivotItem = false; //this variable is used to cancel the navigation when swiping left or right
        public MainPage()
        {
            this.InitializeComponent();

            this.NavigationCacheMode = NavigationCacheMode.Required;

            //ShowStatusBar(false);

            isNewPageInstance = true;
        }

        private async void ShowStatusBar(bool bShow)
        {
            try
            {
                if (bShow)
                {
                    await Windows.UI.ViewManagement.StatusBar.GetForCurrentView().ShowAsync();
                }
                else
                {
                    await Windows.UI.ViewManagement.StatusBar.GetForCurrentView().HideAsync();
                }
            }
            catch(Exception ex)
            {
                Debug.WriteLine(ex.Message.ToString());
            }
        }

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.
        /// This parameter is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            // TODO: Prepare page for display here.

            // TODO: If your application contains multiple pages, ensure that you are
            // handling the hardware Back button by registering for the
            // Windows.Phone.UI.Input.HardwareButtons.BackPressed event.
            // If you are using the NavigationHelper provided by some templates,
            // this event is handled for you.
            if(isNewPageInstance)
            {
                dashboardBrowser.Navigate(new Uri(Constants.dashboardUri));
                statusBrowser.Navigate(new Uri(Constants.statusUri));
                accountBrowser.Navigate(new Uri(Constants.accountUri));
                historyBrowser.Navigate(new Uri(Constants.historyUri));
                helpBrowser.Navigate(new Uri(Constants.helpUri));
            }

            isNewPageInstance = false;
        }

        private void AppBarButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private async void Browser_NavigationCompleted(WebView sender, WebViewNavigationCompletedEventArgs args)
        {
            WebView wb = sender as WebView;

            if(wb != null)
            {
                await wb.InvokeScriptAsync("eval", new string[] { "document.documentElement.style.msTouchAction = 'pan-y';window.addEventListener('pointerdown', function paint(event) {window.external.notify('PointerDown' + ',' + event.clientX + ',' + event.clientY); }, false);window.addEventListener('pointerup', function paint(event) {window.external.notify('PointerUp' + ',' + event.clientX + ',' + event.clientY); }, false);window.addEventListener('mspointerout', function paint(event) {window.external.notify('PointerOut' + ',' + event.clientX + ',' + event.clientY); }, false);" });
            }
        }

        private void Browser_ScriptNotify(object sender, NotifyEventArgs e)
        {
            WebView wb = sender as WebView;

            Debug.WriteLine("bing:" + e.Value.ToString());

            string[] field = e.Value.ToString().Split(',');

            if (field[0] == "PointerDown")
            {
                try
                {
                    if (field[1] != null)
                    {
                        pointerDownX = double.Parse(field[1]);
                    }
                }
                catch (Exception ex)
                {
                    Debug.WriteLine(ex.ToString());
                }

                bPointerDown = true;

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

                if (pointerUpX - pointerDownX > 10 && bPointerDown)
                {
                    bPointerDown = false;

                    if (PivotParent.SelectedIndex > 0)
                    {
                        bSwitchingPivotItem = true;
                       // wb.Stop(); //we call this to prevent the page from being navigated to other pages

                        PivotParent.SelectedIndex--;
                    }
                    else
                    {
                        PivotParent.SelectedIndex = PivotParent.Items.Count - 1;
                    }

                }
                else if (pointerUpX - pointerDownX < -10 && bPointerDown)
                {
                    bPointerDown = false;

                    bSwitchingPivotItem = true;

                    //wb.Stop();

                    if(PivotParent.SelectedIndex < PivotParent.Items.Count - 1)
                    {
                        PivotParent.SelectedIndex++;
                    }
                    else
                    {
                        PivotParent.SelectedIndex = 0;
                    }
                    
                }

            }
        }

        private void BrowserNavigationStarting(WebView sender, WebViewNavigationStartingEventArgs args)
        {
            if(bSwitchingPivotItem)
            {
                args.Cancel = true;

                bSwitchingPivotItem = false;
            }
            //args.Cancel = true;
        }

        private void dashboardBrowser_NavigationStarting(WebView sender, WebViewNavigationStartingEventArgs args)
        {
            Debug.WriteLine("dashboard navigation starting");
            BrowserNavigationStarting(sender, args);
        }

        
        private void statusBrowser_NavigationStarting(WebView sender, WebViewNavigationStartingEventArgs args)
        {
            BrowserNavigationStarting(sender, args);
        }

       
        private void accountBrowser_NavigationStarting(WebView sender, WebViewNavigationStartingEventArgs args)
        {
            BrowserNavigationStarting(sender, args);
        }

        private void historyBrowser_NavigationStarting(WebView sender, WebViewNavigationStartingEventArgs args)
        {
            BrowserNavigationStarting(sender, args);
        }

        private void helpBrowser_NavigationStarting(WebView sender, WebViewNavigationStartingEventArgs args)
        {
            BrowserNavigationStarting(sender, args);
        }

        private void ListBoxItem_Tapped(object sender, TappedRoutedEventArgs e)
        {
            ListBoxItem lbi = sender as ListBoxItem;

            RedeemData rd = new RedeemData();

            if(lbi == seeAllItem)
            {
                //rd.redeemPage = 
            }
            else if(lbi == donateItem)
            {

            }
            else if(lbi == shopItem)
            {

            }
            else if(lbi == winItem)
            {

            }

            Frame.Navigate(typeof(RedeemPage));
        }
    }
}
