import torch
import torch.nn as nn
import torch.nn.functional as F
import pandas as pd

class PUMitigationModel(nn.Module):
    def __init__(self, input_size):
        super(PUMitigationModel, self).__init__()
        self.flatten = nn.Flatten()
        self.fc1 = nn.Linear(input_size, 256)
        self.fc2 = nn.Linear(256, 128)
        self.fc3 = nn.Linear(128, 64)
        self.fc4 = nn.Linear(64, 64)
        self.fc5 = nn.Linear(64, 1)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        x = self.flatten(x)
        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = F.relu(self.fc3(x))
        x = F.relu(self.fc4(x))
        x = self.sigmoid(self.fc5(x))

        return x

def train(loader, model, device, optimizer):
    model.train()
    loss_all = 0

    for x_batch, y_batch in loader:

        x_batch = x_batch.to(device)
        y_batch = y_batch.to(device)
        optimizer.zero_grad()
        out = model(x_batch)

        labels = y_batch.float().view(-1, 1)


        loss =  torch.nn.BCELoss()(out, labels)
        loss.backward()
        optimizer.step()
        loss_all += loss.item()

    return loss_all


def validate(loader, model, device ):
    model.eval()
    loss_all = 0


    for x_batch, y_batch in loader:
        x_batch = x_batch.to(device)
        y_batch = y_batch.to(device)
        out = model(x_batch)

        # out = out.view(-1, out.shape[-1])

        labels = y_batch.float().view(-1, 1)

        loss = torch.nn.BCELoss()(out, labels)
        loss_all += loss.item()
    return loss_all


def test(loader, model, device, outdir):

    model.to(device)
    model.eval()

    nodes_out = []
    labels_test = []

    with torch.no_grad():
        for x_batch, y_batch in loader:
            x_batch = x_batch.to(device, non_blocking=True)

            out = model(x_batch)

            nodes_out.append(out.cpu())
            labels_test.append(y_batch.view(-1, 1).cpu())

    nodes_out = torch.cat(nodes_out, dim=0).squeeze().numpy()
    labels_test = torch.cat(labels_test, dim=0).squeeze().numpy()

    return labels_test, nodes_out

def test_old(loader, model, device, outdir):

    model.to(device)
    model.eval()

    nodes_out = torch.tensor([])
    labels_test = torch.tensor([])


    with torch.no_grad():
        for x_batch, y_batch in loader:
            x_batch = x_batch.to(device)
            y_batch = y_batch.to(device)

            out = model(x_batch)

            labels = y_batch.float().view(-1, 1)

            nodes_out = torch.cat((nodes_out.clone().detach(), out.clone().detach().cpu()), 0)
            labels_test = torch.cat((labels_test.clone().detach(), labels.clone().detach().cpu()), 0)

    labels_test = torch.squeeze(labels_test)
    nodes_out = torch.squeeze(nodes_out)

    labels_test = labels_test.detach().cpu().numpy()
    nodes_out = nodes_out.detach().cpu().numpy()

    # df_out = pd.DataFrame()
    # df_out['labels'] = labels_test
    # df_out['score1'] = nodes_out
    return labels_test, nodes_out
