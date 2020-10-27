module.exports = {
  title: 'BlueMicro nRF52 Keyboard Firmware',
  tagline: 'Keeping simplicity into making BLE Keyboards',
  url: 'http://bluemicro.jpconstantineau.com/',
  baseUrl: '/',
  onBrokenLinks: 'throw',
  favicon: 'data:image/x-icon;base64,AAABAAEAEBAAAAAAAABoBQAAFgAAACgAAAAQAAAAIAAAAAEACAAAAAAAAAEAAAAAAAAAAAAAAAEAAAAAAADzVwEA01UhAO6OXwDzUgcA+JZ6APjUxAD4n4IA81ECAOjo6AD35dcA81cCAPRXGwD4oX0A+c+6APNpMwDLn40A/fHnAPX19QD27+0A+unlANTBugD88+oA81MnAPJJAQD++PUA+dPAAP3p3QDzSQEA/e/lAPNLDADHk34A8kAKAL2vrAD96+AA+JhuAP7x6AD5qoYA81IBAP328wDzUhoA+a2GAPNVAQDyWAEA81gBAPJJAgD//v4A9GQqAPz08QD839EA8k8CAPWVZwDtWhUA7l4SAO1RBQD97uEAx2g6APenfwD+7uEA/efcAPJVAgD97eQA70gOAP7t5AD4zrcA/ePXAPiWbQD96d8A8kQJAOp1PgDXnooA9G0zAPnw7QD08vAA+rmgALd8ZwD4zrgA9GIpAPJKAQD5qIYA7V0fAORnNQDzUwEA2djYAPNWAQD87eYA81kBAPjOuQD+8OYA9fT0APBNAgDxNgkA/ezhAPVuMgD5sY8A4WcuAPmwkgD4lG0A81kCAMaUgADHlIAA////APJFCQDwUAMA8WMYAO/UywDtTwYA9X1LAPmxkADySyIAyJJ+ALWqpwDyVCoA0F0rAM1vQwDBmokA/uvdAOmFXwDxTgEA+KqDAPvj2wDzTgEAxV00APRlLAD25d4Awb28APF6RAD97OMA81QBAPFFAgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAZGRkZGRkEQgIEWRkZGRkZGRkZGRIRXFwN0p8ZGRkZGRkZGQSUDsdKBs7AW5kZGRkZGRkdCoKQyMkGyt5UmRkZGRkR2kDB2VXPE4sNSBkZGRkZAUXa11aNhYVOHVyZGRkZGQNfwtABiFBW0YpYmRkZGRkS1MpJzAtfnolVR5kZGRkZD8ACk0EZEmACmFtZGRkZGRWU01gQhg6XywrY2RkZGRkGXgiHG9zbBB2MQ9kZGRkZFRZalwfOQwaDmYUZGRkZGRkfSkpZRA+TFFeWGRkZGRkZHdnAD0JLiU0aGRkZGRkZGRkZDJPRDMCe2RkZGRkZGRkZGRkJhMvZGRkZGRkZAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=',
  organizationName: 'jpconstantineau', 
  projectName: 'BlueMicro_BLE', 
  themeConfig: {
    navbar: {
      title: 'BlueMicro nRF52 Keyboard Firmware',
      logo: {
        alt: 'BlueMicro Logo',
        src: 'img/logo.png',
      },
      items: [
        {
          to: 'docs/',
          activeBasePath: 'docs',
          label: 'Docs',
          position: 'left',
        },
        {to: 'blog', label: 'Blog', position: 'left'},
        {
          href: 'https://github.com/jpconstantineau/BlueMicro_BLE',
          label: 'GitHub',
          position: 'right',
        },
      ],
    },
    footer: {
      style: 'dark',
      links: [
        {
          title: 'Docs',
          items: [
            {
              label: 'Getting Started',
              to: 'docs/',
            },
          ],
        },
        {
          title: 'Community',
          items: [
            {
              label: 'Discord',
              href: 'https://discord.gg/ecnCR9P',
            },
            {
              label: 'YouTube',
              href: 'https://www.youtube.com/channel/UCFpGp4hHe03nvF9c8_gF_jA',
            },
          ],
        },
        {
          title: 'More',
          items: [
            {
              label: 'Blog',
              to: 'blog',
            },
            {
              label: 'GitHub',
              href: 'https://github.com/jpconstantineau/BlueMicro_BLE',
            },
          ],
        },
      ],
      copyright: `Copyright © ${new Date().getFullYear()} Pierre Constantineau. Built with Docusaurus.`,
    },
  },
  presets: [
    [
      '@docusaurus/preset-classic',
      {
        docs: {
          sidebarPath: require.resolve('./sidebars.js'),
          // Please change this to your repo.
          editUrl:
            'https://github.com/facebook/docusaurus/edit/master/website/',
        },
        blog: {
          showReadingTime: true,
          // Please change this to your repo.
          editUrl:
            'https://github.com/facebook/docusaurus/edit/master/website/blog/',
        },
        theme: {
          customCss: require.resolve('./src/css/custom.css'),
        },
      },
    ],
  ],
};
