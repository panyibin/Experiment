using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel.Email;
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

namespace App8._1
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            this.NavigationCacheMode = NavigationCacheMode.Required;
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
        }

        private void Search_Click(object sender, RoutedEventArgs e)
        {
            string uriToLaunch = @"http://www.bing.com/images/search?q=%E4%BD%A0%E5%A5%BD";
            var uri = new Uri(uriToLaunch);

            LaunchUri(uri);

        }

        async void LaunchUri(Uri uri)
        {
            await Windows.System.Launcher.LaunchUriAsync(uri);
        }

        private void GoToPivot_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(PivotPage));
        }

        private void AppBarButton_Click(object sender, RoutedEventArgs e)
        {
            var statusBar = Windows.UI.ViewManagement.StatusBar.GetForCurrentView();

            //statusBar.ProgressIndicator.ProgressValue = 0.5;
            statusBar.ProgressIndicator.Text = "loading";

            statusBar.ProgressIndicator.ShowAsync();
        }

        private void AppBarButton_Click_1(object sender, RoutedEventArgs e)
        {
            var statusBar = Windows.UI.ViewManagement.StatusBar.GetForCurrentView();

            //statusBar.ProgressIndicator.ProgressValue = 0;

            statusBar.ProgressIndicator.HideAsync();
        }

        private async void LaunchGoogle_Click(object sender, RoutedEventArgs e)
        {
            await Windows.System.Launcher.LaunchUriAsync(new Uri("http://www.google.com"));
        }

        private async void SendEmail_Click(object sender, RoutedEventArgs e)
        {
            await Windows.System.Launcher.LaunchUriAsync(new Uri("mailto:yibinpan@microsoft.com?subject=hello world&body=world"));
        }

        private async void SendEmail2_Click(object sender, RoutedEventArgs e)
        {
            EmailRecipient sendTo = new EmailRecipient()
            {
                Address = "yibinpan@outlook.com"
            };

            EmailMessage mail = new EmailMessage();
            mail.Subject = "google";
            mail.Body = "\n\n\nmail body";
            mail.To.Add(sendTo);
            mail.CC.Add(sendTo);

            await EmailManager.ShowComposeNewEmailAsync(mail);

        }
    }
}
