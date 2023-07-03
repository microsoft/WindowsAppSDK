// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachExtension.Models;
using Azure.Core;
using Azure.Identity;
using Azure.ResourceManager.Storage;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Security.Claims;
using System.Threading;
using System.Threading.Tasks;

namespace AppAttachExtension.Providers
{
    public class IdentityProvider
    {
        private readonly IdentityViewModel _viewModel;
        private List<Claim> _claims;

        public IdentityProvider()
        {
            _viewModel = new IdentityViewModel();
            _claims = new List<Claim>();
        }

        /// <summary>
        /// To populate user identity details
        /// </summary>
        /// <returns></returns>
        public async Task<bool> PopulateUserIdentityAsync()
        {
            var credential = new VisualStudioCredential();
            TokenRequestContext context = new TokenRequestContext(new string[] { "https://management.azure.com/.default" });
            CancellationTokenSource cancellationTokenSource = new CancellationTokenSource();
            CancellationToken cancellationToken = cancellationTokenSource.Token;
            var token = await credential.GetTokenAsync(context, cancellationToken);
            if (token.Token != null)
            {
                _viewModel.JwtToken = token.Token;
                var handler = new JwtSecurityTokenHandler();
                var jsonToken = handler.ReadToken(token.Token) as JwtSecurityToken;
                if (jsonToken != null)
                {
                    _claims = jsonToken.Claims.ToList();
                    var upn = _claims.First(c => c.Type == "upn")?.Value;
                    _viewModel.Upn = upn;
                    var userName = _claims.First(c => c.Type == "name")?.Value;
                    _viewModel.UserName = userName;
                    var userEmail = _claims.First(c => c.Type == "unique_name")?.Value;
                    _viewModel.UserEmail = userEmail;
                }
                return true;
            }
            return false;
        }

        public void PopulateStorageConnectionString(StorageAccountResource storageAccount)
        {
            if (storageAccount != null)
            {
                var key = storageAccount.GetKeys()?.First()?.Value;
                var storageAccountName = storageAccount.Data.Name;
                if (!string.IsNullOrEmpty(key) && !string.IsNullOrEmpty(storageAccountName))
                {
                    _viewModel.StorageAccountConnectionString = $"DefaultEndpointsProtocol=https;AccountName={storageAccountName};AccountKey={key};EndpointSuffix=core.windows.net";
                }
            }
        }

        public IdentityViewModel GetModel()
        {
            return _viewModel;
        }
    }
}
